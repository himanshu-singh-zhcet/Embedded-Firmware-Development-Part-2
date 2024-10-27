/*
 * msp.c
 *
 *  Created on: Jul 29, 2024
 *      Author: Himanshu Singh
 */

#include "main.h"

// Low level Initialization
void HAL_MspInit(void){
	 //Here will do low level processor specific inits.

	//1. Set up the priority grouping of the arm cortex mx processor
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	//2. Enable the required system exceptions of the arm cortex mx processor
	SCB->SHCSR |= 0x7 << 16; //usage fault, memory fault and bus fault system exceptions

	//3. configure the priority for the system exceptions
	HAL_NVIC_SetPriority(MemoryManagement_IRQn,0,0);
	HAL_NVIC_SetPriority(BusFault_IRQn,0,0);
	HAL_NVIC_SetPriority(UsageFault_IRQn,0,0);
}

// Low Level Initialization relate to timer 3 Peripheral
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htimer){
	// 1. enable the clock for the TIM3 Peripheral
	__HAL_RCC_TIM3_CLK_ENABLE();

	// 2. enable the IRQ of TIM3
	HAL_NVIC_EnableIRQ(29);

	// 3. setup the Priority for TIM3
	HAL_NVIC_SetPriority(29,15,0);

}
