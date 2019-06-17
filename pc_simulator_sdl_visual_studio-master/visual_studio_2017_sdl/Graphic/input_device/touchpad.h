/*
 * touchpad.h
 *
 *  Created on: Jun 8, 2019
 *      Author: boome
 */

#ifndef GRAPHIC_INPUT_DEVICE_TOUCHPAD_H_
#define GRAPHIC_INPUT_DEVICE_TOUCHPAD_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "stm32f7xx_hal.h"
#include "cmsis_os.h"
#include "ApplicationConfig.h"
#include "stm32f769i_discovery.h"
#include "stm32f769i_discovery_ts.h"
#include "lvgl.h"


extern bool touchpad_read(lv_indev_data_t *data);

#ifdef __cplusplus
}
#endif

#endif /* GRAPHIC_INPUT_DEVICE_TOUCHPAD_H_ */
