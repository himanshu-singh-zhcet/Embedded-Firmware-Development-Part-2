/*
 * main.c
 *
 *  Created on: Jul 21, 2024
 *      Author: Himanshu Singh
 */
#include<string.h>
#include "stm32f4xx_hal.h"
#include"main.h"



void UART2_Init();
void Error_Handler(void);


UART_HandleTypeDef huart2;



int main(void){
	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;
	char msg[100];
	HAL_Init();



	memset(&osc_init,0,sizeof(osc_init));
	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc_init.HSEState = RCC_HSE_BYPASS;
	if(HAL_RCC_OscConfig(&osc_init) != HAL_OK){
		Error_Handler();
	}

	clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
	    	                         RCC_CLOCKTYPE_PCLK1  | RCC_CLOCKTYPE_PCLK2;
    clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
    clk_init.AHBCLKDivider = RCC_SYSCLK_DIV2;
    clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
    clk_init.APB2CLKDivider = RCC_HCLK_DIV2;
    if(HAL_RCC_ClockConfig(&clk_init,FLASH_ACR_LATENCY_0WS) != HAL_OK){
    	Error_Handler();
    }

    // system clock is now sourced by HSE
    __HAL_RCC_HSI_DISABLE(); // Disabling HSI saves some current

    // LETS REDO THE SYSTICK CONFIGURATION
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    UART2_Init();


    memset(msg,0,sizeof(msg));
    sprintf(msg,"SYSCLK : %ld\r\n",HAL_RCC_GetSysClockFreq());
    HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);

    memset(msg,0,sizeof(msg));
    sprintf(msg,"HCLK : %ld\r\n",HAL_RCC_GetHCLKFreq());
    HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);

    memset(msg,0,sizeof(msg));
    sprintf(msg,"PCLK1 : %ld\r\n",HAL_RCC_GetPCLK1Freq());
    HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);

    memset(msg,0,sizeof(msg));
    sprintf(msg,"PCLK2 : %ld\r\n",HAL_RCC_GetPCLK2Freq());
    HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);

    return 0;
}



// High Level Initialization
void UART2_Init(){
    huart2.Instance  =  USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart2) != HAL_OK){
    	// There is a Problem
        Error_Handler();
      }
}


void Error_Handler(void){
  __disable_irq();
  while (1){
  }

}


