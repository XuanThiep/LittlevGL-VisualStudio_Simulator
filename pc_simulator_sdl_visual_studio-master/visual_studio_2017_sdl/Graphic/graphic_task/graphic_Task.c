/*
 * graphicTask.c
 *
 *  Created on: May 26, 2019
 *      Author: boome
 */

#include "graphic_Task.h"


static void tft_flush(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p);
static void copy_buffer(const uint16_t *pSrc, uint16_t *pDst, uint16_t x, uint16_t y, uint16_t xsize, uint16_t ysize);

static void gpu_mem_blend(lv_color_t * dest, const lv_color_t * src, uint32_t length, lv_opa_t opa);
static void gpu_mem_fill(lv_color_t * dest, uint32_t length, lv_color_t color);

static void dma2d_config(void);
static void littlevgl_graphic_init(void);


extern LTDC_HandleTypeDef hltdc_discovery;
extern DSI_HandleTypeDef hdsi_discovery;
extern DMA2D_HandleTypeDef hdma2d_discovery;
static __IO uint16_t* my_fb = (__IO uint16_t*)(LCD_FB_START_ADDRESS);




void graphicTask_Function(void const * argument)
{
	static uint32_t CPU_Usage_Period = 0;

	littlevgl_graphic_init();

	DBG("Graphic Task Init Done !\n");

	for(;;)
	{
		lv_task_handler();

		/* Monitor CPU Usage */
		if((osKernelSysTick()- CPU_Usage_Period) > CALCULATION_PERIOD)
		{
			CPU_Usage_Period = osKernelSysTick();
			DBG("CPU = %02d\n",osGetCPUUsage());
			BSP_LED_Toggle(LED_GREEN);
		}
		osDelay(5);
	}
}



void littlevgl_graphic_init(void)
{
	lv_disp_drv_t disp_drv;
	lv_indev_drv_t indev_drv_touchpad;
	lv_indev_drv_t indev_drv_encoder;


	/* littlevgl Init */
	lv_init();


	/* Low level display init */
	BSP_LED_Init(LED_GREEN);
	BSP_LED_Init(LED_RED);
	BSP_LCD_Init();
	BSP_LCD_LayerDefaultInit(0, LCD_FB_START_ADDRESS);
	BSP_LCD_SelectLayer(0);
	BSP_LCD_SetBrightness(100);


	/* Init display driver */
	dma2d_config();
	lv_disp_drv_init(&disp_drv);
	disp_drv.disp_flush = tft_flush;
	disp_drv.mem_blend = gpu_mem_blend;
	disp_drv.mem_fill = gpu_mem_fill;
	lv_disp_drv_register(&disp_drv);


	/* Input device touchpad Init  */
	BSP_TS_Init(BSP_LCD_GetXSize(),BSP_LCD_GetYSize());

	lv_indev_drv_init(&indev_drv_touchpad);
	indev_drv_touchpad.read = touchpad_read;
	indev_drv_touchpad.type = LV_INDEV_TYPE_POINTER;
	lv_indev_drv_register(&indev_drv_touchpad);


	/* Input device rotary encoder Init  */
	rotary_encoder_init();

	lv_indev_drv_init(&indev_drv_encoder);
	indev_drv_encoder.read = rotary_encoder_read;
	indev_drv_encoder.type = LV_INDEV_TYPE_ENCODER;
	encoder_input_device = lv_indev_drv_register(&indev_drv_encoder);

	/* Load first screen */
	load_new_screen(NULL,&screen0, Screen0_Init);

}


static void tft_flush(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p)
{
	/*Return if the area is out the screen*/
	if(x2 < 0) return;
	if(y2 < 0) return;
	if(x1 > LV_HOR_RES - 1) return;
	if(y1 > LV_VER_RES - 1) return;

	copy_buffer((const uint16_t *)color_p,(uint16_t *) my_fb, x1, y1, (x2 - x1 + 1), (y2 - y1 + 1));
	lv_flush_ready();
}


static void copy_buffer(const uint16_t *pSrc, uint16_t *pDst, uint16_t x, uint16_t y, uint16_t xsize, uint16_t ysize)
{

	HAL_DMA2D_PollForTransfer(&hdma2d_discovery, 100);

	uint32_t destination = (uint32_t)pDst + (y * LV_HOR_RES + x) *2;
	uint32_t source      = (uint32_t)pSrc;

	/*##-1- Configure the DMA2D Mode, Color Mode and output offset #############*/
	hdma2d_discovery.Init.Mode         = DMA2D_M2M;
	hdma2d_discovery.Init.ColorMode    = DMA2D_OUTPUT_RGB565;
	hdma2d_discovery.Init.OutputOffset = 800 - xsize;
	hdma2d_discovery.Init.AlphaInverted = DMA2D_REGULAR_ALPHA;  /* No Output Alpha Inversion*/
	hdma2d_discovery.Init.RedBlueSwap   = DMA2D_RB_REGULAR;     /* No Output Red & Blue swap */

	/*##-2- DMA2D Callbacks Configuration ######################################*/
	hdma2d_discovery.XferCpltCallback  = NULL;

	/*##-3- Foreground Configuration ###########################################*/
	hdma2d_discovery.LayerCfg[0].AlphaMode = DMA2D_NO_MODIF_ALPHA;
	hdma2d_discovery.LayerCfg[0].InputAlpha = 0xFF;
	hdma2d_discovery.LayerCfg[0].InputColorMode = DMA2D_INPUT_RGB565;
	hdma2d_discovery.LayerCfg[0].InputOffset = 0;
	hdma2d_discovery.LayerCfg[0].RedBlueSwap = DMA2D_RB_REGULAR; /* No ForeGround Red/Blue swap */
	hdma2d_discovery.LayerCfg[0].AlphaInverted = DMA2D_REGULAR_ALPHA; /* No ForeGround Alpha inversion */

	hdma2d_discovery.Instance          = DMA2D;

	/* DMA2D Initialization */
	HAL_DMA2D_Init(&hdma2d_discovery);

	HAL_DMA2D_ConfigLayer(&hdma2d_discovery, 0);

	HAL_DMA2D_Start(&hdma2d_discovery, source, destination, xsize, ysize);

}



static void gpu_mem_blend(lv_color_t * dest, const lv_color_t * src, uint32_t length, lv_opa_t opa)
{
	/*	Wait for the previous operation	*/
	HAL_DMA2D_PollForTransfer(&hdma2d_discovery, 100);

	hdma2d_discovery.Init.Mode         = DMA2D_M2M_BLEND;
	hdma2d_discovery.Init.ColorMode    = DMA2D_OUTPUT_RGB565;
	hdma2d_discovery.Init.OutputOffset = 0x0;
	hdma2d_discovery.Instance   = DMA2D;
	HAL_DMA2D_Init(&hdma2d_discovery);


	hdma2d_discovery.LayerCfg[1].AlphaMode = DMA2D_REPLACE_ALPHA;
	hdma2d_discovery.LayerCfg[1].InputAlpha = opa;
	hdma2d_discovery.LayerCfg[1].InputColorMode = DMA2D_OUTPUT_RGB565;
	hdma2d_discovery.LayerCfg[1].InputOffset = 0x0;
	HAL_DMA2D_ConfigLayer(&hdma2d_discovery, 1);

	HAL_DMA2D_BlendingStart(&hdma2d_discovery, (uint32_t)src, (uint32_t)dest, (uint32_t)dest, length, 1);
}


static void gpu_mem_fill(lv_color_t * dest, uint32_t length, lv_color_t color)
{
	/*	Wait for the previous operation	*/
	HAL_DMA2D_PollForTransfer(&hdma2d_discovery, 100);

	hdma2d_discovery.Init.Mode         = DMA2D_R2M;
	hdma2d_discovery.Init.ColorMode    = DMA2D_OUTPUT_RGB565 ;
	hdma2d_discovery.Init.OutputOffset = 0x0;
	hdma2d_discovery.Instance   = DMA2D;
	HAL_DMA2D_Init(&hdma2d_discovery);

	hdma2d_discovery.LayerCfg[1].AlphaMode = DMA2D_REPLACE_ALPHA;
	hdma2d_discovery.LayerCfg[1].InputAlpha = 0xFF;
	hdma2d_discovery.LayerCfg[1].InputColorMode = DMA2D_OUTPUT_RGB565;
	hdma2d_discovery.LayerCfg[1].InputOffset = 0x0;
	HAL_DMA2D_ConfigLayer(&hdma2d_discovery, 1);

	HAL_DMA2D_BlendingStart(&hdma2d_discovery, (uint32_t) lv_color_to32(color), (uint32_t) dest, (uint32_t)dest, length, 1);
}


static void dma2d_config(void)
{
	/* Configure the DMA2D Mode, Color Mode and output offset */
	hdma2d_discovery.Init.Mode         = DMA2D_M2M_BLEND;
	hdma2d_discovery.Init.ColorMode    = DMA2D_OUTPUT_RGB565 ;
	hdma2d_discovery.Init.OutputOffset = 0x0;

	/* Foreground Configuration */
	hdma2d_discovery.LayerCfg[1].AlphaMode = DMA2D_REPLACE_ALPHA;
	hdma2d_discovery.LayerCfg[1].InputAlpha = 0xFF;
	hdma2d_discovery.LayerCfg[1].InputColorMode = DMA2D_OUTPUT_RGB565;
	hdma2d_discovery.LayerCfg[1].InputOffset = 0x0;

	/* Background Configuration */
	hdma2d_discovery.LayerCfg[0].AlphaMode = DMA2D_REPLACE_ALPHA;
	hdma2d_discovery.LayerCfg[0].InputAlpha = 0xFF;
	hdma2d_discovery.LayerCfg[0].InputColorMode = DMA2D_OUTPUT_RGB565;
	hdma2d_discovery.LayerCfg[0].InputOffset = 0x0;

	hdma2d_discovery.Instance   = DMA2D;

	/* DMA2D Initialization */
	HAL_DMA2D_Init(&hdma2d_discovery);

	HAL_DMA2D_ConfigLayer(&hdma2d_discovery, 0);
	HAL_DMA2D_ConfigLayer(&hdma2d_discovery, 1);
}





