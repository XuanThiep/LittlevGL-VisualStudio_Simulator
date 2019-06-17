/*
 * graphicTask.h
 *
 *  Created on: May 26, 2019
 *      Author: boome
 */

#ifndef GRAPHIC_GRAPHIC_TASK_GRAPHIC_TASK_H_
#define GRAPHIC_GRAPHIC_TASK_GRAPHIC_TASK_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "cmsis_os.h"
#include "ApplicationConfig.h"
#include "stm32f769i_discovery.h"
#include "stm32f769i_discovery_sdram.h"
#include "stm32f769i_discovery_lcd.h"
#include "stm32f769i_discovery_ts.h"
#include "cpu_utils.h"
#include "lvgl.h"

#include "graphic_common.h"
#include "testThemes.h"
#include "rotary_encoder.h"
#include "touchpad.h"


extern void graphicTask_Function(void const * argument);


#ifdef __cplusplus
}
#endif


#endif /* GRAPHIC_GRAPHIC_TASK_GRAPHIC_TASK_H_ */
