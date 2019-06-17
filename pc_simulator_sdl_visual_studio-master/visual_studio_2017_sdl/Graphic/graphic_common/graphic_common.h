/*
 * graphic_common.h
 *
 *  Created on: Jun 8, 2019
 *      Author: boome
 */

#ifndef GRAPHIC_GRAPHIC_COMMON_GRAPHIC_COMMON_H_
#define GRAPHIC_GRAPHIC_COMMON_GRAPHIC_COMMON_H_


#ifdef __cplusplus
extern "C" {
#endif
#include "lvgl/lvgl.h"

#define DBG		printf

/* Global input device handle*/
extern lv_indev_t* encoder_input_device;

/* Global screen handle */
extern lv_obj_t* screen0;
extern lv_obj_t* screen1;

void load_new_screen(lv_obj_t** current_scr, lv_obj_t** destination_scr, void (*destination_Init)(void));
 void Screen0_Init(void);
 void Screen1_Init(void);


#ifdef __cplusplus
}
#endif


#endif /* GRAPHIC_GRAPHIC_COMMON_GRAPHIC_COMMON_H_ */
