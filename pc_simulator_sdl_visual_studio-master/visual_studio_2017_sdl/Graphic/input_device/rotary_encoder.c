/*
 * rotary_encoder.c
 *
 *  Created on: Jun 7, 2019
 *      Author: boome
 */

#include	"rotary_encoder.h"

/* Declaring Variable */
TIM_HandleTypeDef htim8;
static volatile int8_t _encoder_steps	= 0;


/* Declaring Static Function Prototype */
static 	void MX_TIM8_Init(void);
static	int8_t rotary_encoder_get_step(void);
static	void rotary_encoder_reset_step(void);
static	uint8_t rotary_encoder_get_button(void);






/* TIM8 init function */
static void MX_TIM8_Init(void)
{
	TIM_Encoder_InitTypeDef sConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};

	htim8.Instance = TIM8;
	htim8.Init.Prescaler = 0;
	htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim8.Init.Period = 3;
	htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim8.Init.RepetitionCounter = 0;
	htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
	sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
	sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
	sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
	sConfig.IC1Filter = 10;
	sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
	sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
	sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
	sConfig.IC2Filter = 10;
	HAL_TIM_Encoder_Init(&htim8, &sConfig);

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

	HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig);
}


static uint8_t rotary_encoder_get_button(void)
{
	return HAL_GPIO_ReadPin(ROTARY_ENCODER_BUTTON_PORT, ROTARY_ENCODER_BUTTON_PIN);
}


static int8_t rotary_encoder_get_step(void)
{
	return _encoder_steps;
}


static void rotary_encoder_reset_step(void)
{
	_encoder_steps = 0;
}


void rotary_encoder_callback(void)
{
	_encoder_steps = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim8) ? -1 : 1;
}


void rotary_encoder_init(void)
{

	MX_TIM8_Init();
	__HAL_TIM_ENABLE_IT(&htim8, TIM_IT_UPDATE);
	HAL_TIM_Encoder_Start(&htim8,TIM_CHANNEL_ALL);
}


bool rotary_encoder_read(lv_indev_data_t *data)
{
	data->enc_diff = rotary_encoder_get_step();

	rotary_encoder_reset_step();

	if(!rotary_encoder_get_button())
	{
		data->state = LV_INDEV_STATE_PR;
	}
	else
	{
		data->state = LV_INDEV_STATE_REL;
	}
	//DBG("enc_diff = %d, state = %d\n",data->enc_diff,data->state);

	return false; /*No buffering so no more data read*/
}


void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef* tim_encoderHandle)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitTypeDef SW_GPIO_InitStruct = {0};

	if(tim_encoderHandle->Instance==TIM8)
	{
		/* USER CODE BEGIN TIM8_MspInit 0 */
		/* TIM8 interrupt Init */
		HAL_NVIC_SetPriority(TIM8_UP_TIM13_IRQn, 8, 0);
		HAL_NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);

		/* USER CODE END TIM8_MspInit 0 */

		/* TIM8 clock enable */
		__HAL_RCC_TIM8_CLK_ENABLE();

		__HAL_RCC_GPIOC_CLK_ENABLE();

		/*
		 * 	TIM8 GPIO Configuration
		 *	PC7     ------> TIM8_CH2
		 *	PC6     ------> TIM8_CH1
		 */

		GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_6;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF3_TIM8;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		/* USER CODE BEGIN TIM8_MspInit 1 */

		/* Init for button of rotary encoder */
		__HAL_RCC_GPIOJ_CLK_ENABLE();

		SW_GPIO_InitStruct.Pin = ROTARY_ENCODER_BUTTON_PIN;
		SW_GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		SW_GPIO_InitStruct.Pull = GPIO_PULLUP;
		SW_GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		HAL_GPIO_Init(ROTARY_ENCODER_BUTTON_PORT, &SW_GPIO_InitStruct);

		/* USER CODE END TIM8_MspInit 1 */
	}
}


void TIM8_UP_TIM13_IRQHandler(void)
{
	/* USER CODE BEGIN TIM8_UP_TIM13_IRQn 0 */

	/* USER CODE END TIM8_UP_TIM13_IRQn 0 */
	HAL_TIM_IRQHandler(&htim8);
	/* USER CODE BEGIN TIM8_UP_TIM13_IRQn 1 */

	/* USER CODE END TIM8_UP_TIM13_IRQn 1 */
}
