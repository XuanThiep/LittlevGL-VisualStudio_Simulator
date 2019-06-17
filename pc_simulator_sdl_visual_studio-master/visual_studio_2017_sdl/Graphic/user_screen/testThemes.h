/**
 * @file lv_test_theme_2.h
 *
 */

#ifndef LV_TEST_THEME_2_H
#define LV_TEST_THEME_2_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lvgl.h"
#include "lv_ex_conf.h"
#else
#include "lvgl/lvgl.h"
#endif

#define USE_LV_TESTS	1

#if USE_LV_TESTS

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Test run time theme change
 */
void lv_test_theme_2(void);

/**********************
 *      MACROS
 **********************/

#endif /*USE_LV_TESTS*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_TEST_THEME_2_H*/