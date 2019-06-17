/*
 * window1.c
 *
 *  Created on: Jun 8, 2019
 *      Author: boome
 */
#include "screen1.h"


static lv_res_t btn_change_on_click1(lv_obj_t * btn);
static lv_obj_t* label_info1;
static lv_obj_t* btnChange1;
static lv_obj_t* btnChange_Label1 ;


void Screen1_Init(void)
{
	DBG("Init Screen 1\n");
	screen1 = lv_obj_create(NULL,NULL);

	btnChange1 = lv_btn_create(screen1, NULL);
	btnChange_Label1 = lv_label_create(btnChange1, NULL);

	lv_label_set_text(btnChange_Label1, SYMBOL_CALL);
	lv_obj_set_pos(btnChange1, 200,120);
	lv_obj_set_free_num(btnChange1, BTN_CHANGE_ID_1);
	lv_btn_set_action(btnChange1, LV_BTN_ACTION_CLICK, btn_change_on_click1);

	label_info1 = lv_label_create(screen1, NULL);
	lv_obj_set_pos(label_info1, 700,300);
}


static lv_res_t btn_change_on_click1(lv_obj_t * btn)
{
	if(lv_obj_get_free_num(btn) == BTN_CHANGE_ID_1)
	{
		lv_label_set_text(label_info1, "HEHE !!!");
		load_new_screen(&screen1, &screen0, Screen0_Init);
	}

	return LV_RES_OK;
}
