/*
 * main.c
 *
 *  Created on: Jul 21, 2024
 *      Author: Himanshu Singh
 */
#include<string.h>
#include "stm32f4xx_hal.h"
#include"main.h"



void Error_Handler(void);
void SystemClockConfig(void);
void TIMER2_Init(void);
TIM_HandleTypeDef  htimer2;


int main(void){


    while(1);
    return 0;
}

void TIMER2_Init(void){
	//htimer2.
}

void Error_Handler(void){
  __disable_irq();
  while (1){
  }

}


