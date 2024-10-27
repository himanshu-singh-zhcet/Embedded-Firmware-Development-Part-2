/*
 * main.c
 *
 *  Created on: Jul 21, 2024
 *      Author: Himanshu Singh
 */
#include<string.h>
#include "stm32f4xx_hal.h"
#include"main.h"

#define TRUE 1
#define FALSE 0
void SystemClockConfig(void);
void UART2_Init();
void Error_Handler(void);
uint8_t convert_to_capital(uint8_t data);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

UART_HandleTypeDef huart2;

char *user_data = "The Application is running \r\n";
uint8_t data_buffer[100];
uint8_t received_data;
uint32_t count = 0;
uint8_t reception_complete = FALSE;
int main(void){
	HAL_Init();
	SystemClockConfig();
	UART2_Init();

	uint16_t len_of_data = strlen(user_data);
	HAL_UART_Transmit(&huart2,(uint8_t*)user_data,len_of_data,HAL_MAX_DELAY);

	while(reception_complete != TRUE){
	HAL_UART_Receive_IT(&huart2,&received_data,1);
	}
	while(1);

	return 0;
}

void SystemClockConfig(void){

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
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(received_data == '\r'){
		reception_complete = TRUE;
		data_buffer[count++] = '\r';
		HAL_UART_Transmit(&huart2, data_buffer, count, HAL_MAX_DELAY);
	}
	else{
		data_buffer[count++] =  received_data;
	}
}

uint8_t convert_to_capital(uint8_t data){
	if(data>= 'a' && data <= 'z'){
		data = data - ('a' - 'A');
	}
	return data;
}

void Error_Handler(void){
  __disable_irq();
  while (1){
  }

}


