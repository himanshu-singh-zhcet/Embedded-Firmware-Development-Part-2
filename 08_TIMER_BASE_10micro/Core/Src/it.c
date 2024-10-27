/*
 * it.c
 *
 *  Created on: Jul 29, 2024
 *      Author: Himanshu Singh
 */


#include "stm32f4xx_hal.h"

void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void TIM3_IRQHandler(void){
	HAL_TIM_IRQHandler(&htimer3);
}
