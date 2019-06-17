/*
 * graphic_common.c
 *
 *  Created on: Jun 8, 2019
 *      Author: boome
 */

#include "graphic_common.h"


lv_indev_t* encoder_input_device;
lv_obj_t* screen0;
lv_obj_t* screen1;

void load_new_screen(lv_obj_t** current_scr, lv_obj_t** destination_scr, void (*destination_Init)(void))
{
	destination_Init();
	lv_scr_load(*destination_scr);

	if(current_scr != NULL)
	{
		lv_obj_del(*current_scr);
	}
}


