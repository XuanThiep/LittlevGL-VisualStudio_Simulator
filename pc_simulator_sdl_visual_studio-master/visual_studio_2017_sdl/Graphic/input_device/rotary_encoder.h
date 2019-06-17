/*
 * rotary_encoder.h
 *
 *  Created on: Jun 7, 2019
 *      Author: boome
 */

#ifndef GRAPHIC_INPUT_DEVICE_ROTARY_ENCODER_H_
#define GRAPHIC_INPUT_DEVICE_ROTARY_ENCODER_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Include Library */
#include "stm32f7xx_hal.h"
#include "cmsis_os.h"
#include "ApplicationConfig.h"
#include "lvgl.h"


/* Define variables */
#define	ROTARY_ENCODER_BUTTON_PORT		GPIOJ
#define	ROTARY_ENCODER_BUTTON_PIN		GPIO_PIN_1





extern	TIM_HandleTypeDef htim8;

extern	void rotary_encoder_callback(void);
extern	void rotary_encoder_init(void);
extern	bool rotary_encoder_read(lv_indev_data_t *data);



#ifdef __cplusplus
}
#endif

#endif /* GRAPHIC_INPUT_DEVICE_ROTARY_ENCODER_H_ */
