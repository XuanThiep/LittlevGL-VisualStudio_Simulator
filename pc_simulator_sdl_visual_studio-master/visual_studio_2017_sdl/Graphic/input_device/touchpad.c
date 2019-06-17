/*
 * touchpad.c
 *
 *  Created on: Jun 8, 2019
 *      Author: boome
 */

#include	"touchpad.h"




/**
 * Read an input device
 * @param indev_id id of the input device to read
 * @param x put the x coordinate here
 * @param y put the y coordinate here
 * @return true: the device is pressed, false: released
 */
bool touchpad_read(lv_indev_data_t *data)
{
	static int16_t last_x = 0;
	static int16_t last_y = 0;
	static TS_StateTypeDef  TS_State;

	BSP_TS_GetState(&TS_State);

	if(TS_State.touchDetected != 0)
	{
		data->point.x = TS_State.touchX[0];
		data->point.y = TS_State.touchY[0];
		last_x = data->point.x;
		last_y = data->point.y;
		data->state = LV_INDEV_STATE_PR;
		//DBG("\r\nTouch Detected [%d, %d]",data->point.x, data->point.y );
	}
	else
	{
		data->point.x = last_x;
		data->point.y = last_y;
		data->state = LV_INDEV_STATE_REL;
	}

	return false;
}


