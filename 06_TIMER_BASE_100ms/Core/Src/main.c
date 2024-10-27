/*
 * main.c
 *
 *  Created on: 04-Aug-2024
 *      Author: Himanshu Singh
 */


#include "stm32f4xx_hal.h"
#include"main.h"

void SystemClockConfig(void);
void Error_handler(void);
void TIMER3_Init(void);
void GPIO_Init(void);

TIM_HandleTypeDef htimer3;

int main(void){
	HAL_Init();
	SystemClockConfig();
	GPIO_Init();
	TIMER3_Init();

	// lets start the timer
	HAL_TIM_Base_Start(&htimer3);
	while(1){
	    // LOOP until the update event flag is set
	    while(!(TIM3->SR & TIM_SR_UIF)); // UIF BIT OF SR REGISTER
	    // the required delay has been elapsed, user code can be executed
	    TIM3->SR = 0;
	    HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
	}


	return 0;
}

void SystemClockConfig(void){

}


// High Level Initialization
void TIMER3_Init(void){
	htimer3.Instance = TIM3;
	htimer3.Init.Prescaler = 24;
	htimer3.Init.Period = 64000-1;
	if(HAL_TIM_Base_Init(&htimer3) != HAL_OK){
		Error_handler();
	}
}

void GPIO_Init(void){
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef ledpin;
	ledpin.Pin = GPIO_PIN_5;
	ledpin.Mode = GPIO_MODE_OUTPUT_PP;
	ledpin.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA,&ledpin);
}
void Error_handler(void){
  __disable_irq();
  while (1){
  }

}


