/*
 * it.c
 *
 *  Created on: Jul 29, 2024
 *      Author: Himanshu Singh
 */

#include "main.h"

void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

