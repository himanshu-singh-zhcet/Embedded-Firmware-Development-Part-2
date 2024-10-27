/*
 * it.c
 *
 *  Created on: Jul 29, 2024
 *      Author: Himanshu Singh
 */


#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef htimer2;

void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
void TIM2_IRQHandler(void){
	HAL_TIM_IRQHandler(&htimer2); // time required for this function to finish is 5.5us
}
