/*
 * window0.h
 *
 *  Created on: Jun 8, 2019
 *      Author: boome
 */

#ifndef GRAPHIC_USER_SCREEN_SCREEN0_H_
#define GRAPHIC_USER_SCREEN_SCREEN0_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "lvgl/lvgl.h"
#include "../graphic_common/graphic_common.h"
#include "stdio.h"

#define ROL_FRUIT_ID		(0x00)
#define LAB_INFO_ID			(0x01)
#define PAG_MAIN_ID			(0x02)
#define DDL_COLOR_ID		(0x03)

/******************************	Define object parameter ******************************/

/*	Content Header */
#define	CON_HEADER_WIDTH				(LV_HOR_RES)
#define	CON_HEADER_X					(0)
#define	CON_HEADER_Y					(0)


/* 	Page Main */
#define	PAG_MAIN_WIDTH					(LV_HOR_RES)
#define PAG_MAIN_ALIGN_X				(0)
#define PAG_MAIN_ALIGN_Y				(0)
#define PAG_MAIN_SCRL_HEIGHT			(420)


/*	Roller Fruit */
#define ROL_FRUIT_ALIGN_X				(0)
#define	ROL_FRUIT_ALIGN_Y				(40)
#define	ROL_FRUIT_OPTION				"Apple\nMango\nBanana\nCoconut\nStrawberry\nPineapple\nWatermelon\nMangosteen\nLitchi fruit\nDragon fruit"
#define	ROL_FRUIT_VISIBLE_ROW			(3)
#define ROL_FRUIT_ANIMATION_TIME		(100)


/*	Text area infor */
#define LAB_INFO_WIDTH					(PAG_INFO_WIDTH - 20)
#define LAB_INFO_HEIGHT					(PAG_INFO_HEIGHT -3)
#define LAB_INFO_ALIGN_X				(5)
#define LAB_INFOR_ALIGN_Y				(5)


/*	Page infor	*/
#define	PAG_INFO_WIDTH					(LV_HOR_RES)
#define	PAG_INFO_HEIGHT					(150)
#define	PAG_INFO_ALIGN_X				(0)
#define	PAG_INFO_ALIGN_Y				(0)


/*	Drop down list color	*/
#define	DDL_COLOR_WITH					(0)
#define DDL_COLOR_ELEMENT_HEGHT			(20)
#define DDL_COLOR_ALIGN_X				(0)
#define DDL_COLOR_ALIGN_Y				(0)
#define	DDL_COLOR_OPTION				"Red\nBlue\nGreen\nYellow\nWhite\nBlack\nMagenta\nBrown\nViolet\nGray\nSilver\nCyan\nOrange"


#ifdef __cplusplus
}
#endif




#endif /* GRAPHIC_USER_SCREEN_SCREEN0_H_ */
