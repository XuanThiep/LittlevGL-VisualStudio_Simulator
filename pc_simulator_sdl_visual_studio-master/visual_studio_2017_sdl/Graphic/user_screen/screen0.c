/*
 * window0.c
 *
 *  Created on: Jun 8, 2019
 *      Author: boome
 */

#include	"screen0.h"


static lv_group_t* group_control;
static lv_obj_t* con_header;
static lv_obj_t* rol_fruit;
static lv_obj_t* lab_info;
static lv_obj_t* pag_main;
static lv_obj_t* ddl_color;

static void header_init(void);
static void page_main_init(void);
static void roller_fruit_init(void);
static void ddlist_color_init(void);
static void label_infor_init(void);

static lv_res_t roller_fruit_on_select(lv_obj_t* obj);
static lv_res_t ddlist_color_on_select(lv_obj_t* obj);




void Screen0_Init(void)
{

	DBG("Init Screen 0\n");
	screen0 = lv_obj_create(NULL,NULL);


	header_init();
	page_main_init();

	label_infor_init();
	roller_fruit_init();
	ddlist_color_init();

	/*	Create group control */
	group_control = lv_group_create();

	lv_group_add_obj(group_control, rol_fruit);
	lv_group_add_obj(group_control, ddl_color);
	lv_group_add_obj(group_control, lab_info);

	lv_group_set_wrap(group_control, true);

	/* Assign input device encoder to control group */
	lv_indev_set_group(encoder_input_device, group_control);


}


static void header_init(void)
{
	/*	Create header */
	con_header	= 	lv_cont_create(screen0, NULL);

	lv_obj_set_width(con_header, CON_HEADER_WIDTH);
	lv_obj_set_pos(con_header, CON_HEADER_X, CON_HEADER_Y);
	lv_cont_set_fit(con_header, false, true);

	lv_obj_t* lab_header = lv_label_create(con_header, NULL);
	lv_label_set_text(lab_header, "HOME SCREEN");
	lv_obj_align(lab_header, NULL, LV_ALIGN_CENTER, 0, 0);
	
}


static void page_main_init(void)
{
	/* Create main page */
	pag_main = lv_page_create(screen0, NULL);

	lv_obj_set_free_num(pag_main, PAG_MAIN_ID);
	lv_obj_set_size(pag_main, PAG_MAIN_WIDTH, LV_VER_RES - lv_cont_get_fit_height(con_header));
	lv_obj_align(pag_main, con_header, LV_ALIGN_OUT_BOTTOM_LEFT, PAG_INFO_ALIGN_X, PAG_INFO_ALIGN_Y);

	lv_page_set_arrow_scroll(pag_main, true);
	lv_page_set_scrl_fit(pag_main, false, false);
	lv_page_set_scrl_height(pag_main, PAG_MAIN_SCRL_HEIGHT);

}


static void roller_fruit_init(void)
{
	/*	Create fruit roller */
	rol_fruit	=	lv_roller_create(pag_main, NULL);

	lv_obj_set_free_num(rol_fruit, ROL_FRUIT_ID);
	lv_obj_align(rol_fruit, pag_main, LV_ALIGN_IN_TOP_LEFT, ROL_FRUIT_ALIGN_X, ROL_FRUIT_ALIGN_Y);

	lv_obj_t* lab_rol_fruit = lv_label_create(pag_main, NULL);
	
	lv_label_set_text(lab_rol_fruit, "Fruits");
	lv_obj_align(lab_rol_fruit, rol_fruit, LV_ALIGN_OUT_TOP_MID, 25, 0);

	lv_roller_set_options(rol_fruit, ROL_FRUIT_OPTION);
	lv_roller_set_visible_row_count(rol_fruit, ROL_FRUIT_VISIBLE_ROW);
	lv_roller_set_anim_time(rol_fruit, ROL_FRUIT_ANIMATION_TIME);
	lv_roller_set_hor_fit(rol_fruit, true);
	lv_roller_set_action(rol_fruit, roller_fruit_on_select);

}


static void ddlist_color_init(void)
{

	/*	Create drop down list */
	ddl_color = lv_ddlist_create(pag_main, NULL);


	lv_obj_set_free_num(ddl_color, DDL_COLOR_ID);
	lv_obj_align(ddl_color, rol_fruit, LV_ALIGN_OUT_BOTTOM_LEFT, DDL_COLOR_ALIGN_X, DDL_COLOR_ALIGN_Y);

	lv_ddlist_set_options(ddl_color, DDL_COLOR_OPTION);
	lv_ddlist_set_draw_arrow(ddl_color, true);

	lv_ddlist_set_action(ddl_color, ddlist_color_on_select);

}


static void label_infor_init(void)
{
	/*	Create label infor	*/
	lab_info = lv_label_create(pag_main, NULL);

	lv_obj_set_free_num(lab_info, LAB_INFO_ID);
	lv_obj_set_size(lab_info, LAB_INFO_WIDTH, LAB_INFO_HEIGHT);
	lv_obj_align(lab_info, pag_main, LV_ALIGN_IN_BOTTOM_MID, LAB_INFO_ALIGN_X, LAB_INFOR_ALIGN_Y);

	lv_label_set_body_draw(lab_info, true);
	lv_label_set_long_mode(lab_info, LV_LABEL_LONG_BREAK);

}

static lv_res_t roller_fruit_on_select(lv_obj_t* obj)
{
	uint8_t buffer [35];
	uint8_t value [20];

	if(lv_obj_get_free_num(obj) == ROL_FRUIT_ID)
	{
		lv_roller_get_selected_str(rol_fruit,(char*)value);
		snprintf((char*)buffer,35,"\nID: %d, Value: %s ",lv_roller_get_selected(rol_fruit), value);

		DBG((const char*)buffer);
		lv_label_ins_text(lab_info, LV_LABEL_POS_LAST, (const char*)buffer);

		if(strlen(lv_label_get_text(lab_info)) > 5000)
		{
			/* If label length too long, clear this content, to save memory */
			lv_label_set_text(lab_info, "");
		}
		DBG("\nlab_infor length = %d",(uint8_t)strlen(lv_label_get_text(lab_info)));

		/* Scroll page infor to lastest position */
		//lv_page_scroll_ver(pag_info, - PAG_INFO_HEIGHT);
	}

	return LV_RES_OK;
}


static lv_res_t ddlist_color_on_select(lv_obj_t* obj)
{
	if(lv_obj_get_free_num(obj) == DDL_COLOR_ID)
	{
		DBG("\nDDL selected id = %d", lv_ddlist_get_selected(ddl_color));
	}

	return LV_RES_OK;
}




