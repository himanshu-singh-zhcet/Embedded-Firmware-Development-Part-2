/*
 * it.c
 *
 *  Created on: Jul 21, 2024
 *      Author: Himanshu Singh
 */

#include "stm32f4xx_hal.h"

void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

