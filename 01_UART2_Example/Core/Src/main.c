/*
 * main.c
 *
 *  Created on: Jul 21, 2024
 *      Author: Himanshu Singh
 */
#include<string.h>
#include "stm32f4xx_hal.h"
#include"main.h"

void SystemClockConfig(void);
void UART2_Init();
void Error_Handler(void);
uint8_t convert_to_capital(uint8_t data);

UART_HandleTypeDef huart2;
char *user_data = "The Application is running \r\n";
int main(void){
	HAL_Init();
	SystemClockConfig();
	UART2_Init();

	uint16_t len_of_data = strlen(user_data);
	HAL_UART_Transmit(&huart2,(uint8_t*)user_data,len_of_data,HAL_MAX_DELAY);

    uint8_t rcvd_data;
    uint8_t data_buffer[100];
    int count = 0;
    while(1){
    HAL_UART_Receive(&huart2,&rcvd_data,1,HAL_MAX_DELAY);
        if(rcvd_data == '\r'){
    	   break;
        }
        else{
           data_buffer[count++] = convert_to_capital(rcvd_data);
        }
    }
    data_buffer[count++] = '\r';  // putting carage return
    HAL_UART_Transmit(&huart2,data_buffer,count,HAL_MAX_DELAY);
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


