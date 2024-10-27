/*
 * main.c
 *
 *  Created on: 04-Aug-2024
 *      Author: Himanshu Singh
 */


#include "stm32f4xx_hal.h"
#include"main.h"
#include<string.h>

void SystemClockConfig(uint8_t clock_freq);
void Error_handler(void);
void TIMER2_Init(void);
void GPIO_Init(void);
void LSE_Configuration(void);
void UART2_Init(void);

UART_HandleTypeDef huart2;

TIM_HandleTypeDef htimer2;
uint32_t input_capture[2] = {0};
uint8_t count = 1;
uint8_t is_capture_done = FALSE;

int main(void){
	uint32_t capture_difference = 0;
	double timer2_cnt_freq = 0;
	double timer2_cnt_res = 0;
	double user_signal_time_period = 0;
	double user_signal_freq  = 0;
	char usr_msg[100];


	HAL_Init();
	SystemClockConfig(SYS_CLOCK_FREQ_50_MHZ);
	GPIO_Init();
	UART2_Init();
	TIMER2_Init();
	LSE_Configuration();


	while(1){
	    if(is_capture_done){
	    	if(input_capture[1]>input_capture[0]){
	    	    capture_difference = input_capture[1]-input_capture[0];
	    	}
	    	else{
	    		capture_difference = (0XFFFFFFFF - input_capture[0])+input_capture[1];
	    	}

	        timer2_cnt_freq = (HLL_RCC_GetPCLK1Freq()*2)/(htimer2.Init.Prescaler+1);
	        timer2_cnt_res = 1/timer2_cnt_freq;
	        user_signal_time_period = capture_difference*timer2_cnt_res;
	        user_signal_freq = 1/ user_signal_time_period;
	        sprintf(usr_msg,"Frequency of the signal applied = %f\r\n",user_signal_freq);
	        HAL_UART_Transmit(&huart2, usr_msg, strlen(usr_msg), HAL_MAX_DELAY);
	        is_capture_done = FALSE;
	    }

	}


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

// High Level Initialization
void TIMER2_Init(void){
	TIM_IC_InitTypeDef timer2IC_Config;
	htimer2.Instance = TIM2;
	htimer2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htimer2.Init.Prescaler = 1;
	htimer2.Init.Period = 0xFFFFFFFF;
	if(HAL_TIM_IC_Init(&htimer2) != HAL_OK){
		Error_handler();
	}

	timer2IC_Config.ICFilter = 0;
	timer2IC_Config.ICPolarity = TIM_ICPOLARITY_RISING;
	timer2IC_Config.ICPrescaler = TIM_ICPSC_DIV1;
	timer2IC_Config.ICSelection = TIM_ICSELECTION_DIRECTTI;
	if(HAL_TIM_IC_ConfigChannel(&htimer2, &timer2IC_Config, TIM_CHANNEL_1) != HAL_OK){
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

void SystemClockConfig(uint8_t clock_frequency){
	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;

	uint32_t FLatency = 0;
	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSE;
	osc_init.HSIState = RCC_HSI_ON;
	osc_init.LSEState = LSE_LSE_ON;
	osc_init.HSICalibrationValue = 16;
	osc_init.PLL.PLLState = RCC_PLL_ON;
    osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSI;

    switch(clock_frequency){
    case SYS_CLOCK_FREQ_50_MHZ:{
    	 osc_init.PLL.PLLM = 16;
    	 osc_init.PLL.PLLN = 100;
    	 osc_init.PLL.PLLP = 2;
    	 osc_init.PLL.PLLQ  = 2;

    	 clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
    	                         RCC_CLOCKTYPE_PCLK1  | RCC_CLOCKTYPE_PCLK2;
    	 clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    	 clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
    	 clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
    	 clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

    	 FLatency = FLASH_ACR_LATENCY_1WS;
    	 break;
    }
    case SYS_CLOCK_FREQ_84_MHZ:{
    	 osc_init.PLL.PLLM = 16;
    	 osc_init.PLL.PLLN = 168;
    	 osc_init.PLL.PLLP = 2;
    	 osc_init.PLL.PLLQ  = 2;

    	 clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
    	    	                         RCC_CLOCKTYPE_PCLK1  | RCC_CLOCKTYPE_PCLK2;
    	 clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    	 clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
    	 clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
    	 clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

    	 FLatency = FLASH_ACR_LATENCY_2WS;
    	 break;
    }
    case SYS_CLOCK_FREQ_120_MHZ:{
    	 osc_init.PLL.PLLM = 16;
    	 osc_init.PLL.PLLN = 240;
    	 osc_init.PLL.PLLP = 2;
    	 osc_init.PLL.PLLQ  = 2;

    	 clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
    	    	    	                         RCC_CLOCKTYPE_PCLK1  | RCC_CLOCKTYPE_PCLK2;
    	 clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    	 clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
    	 clk_init.APB1CLKDivider = RCC_HCLK_DIV4;
    	 clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

    	 FLatency = FLASH_ACR_LATENCY_3WS;
    	 break;
    }
    default:
    	return;
    }
    if(HAL_RCC_OscConfig(&osc_init) != HAL_OK){
    	Error_Handler();
    }
    if(HAL_RCC_ClockConfig(&clk_init,FLatency) != HAL_OK){
    		Error_Handler();
    }

    //Systick configuration
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
}

void LSE_Configuration(void){
#if 0
	RCC_OscInitTypeDef Osc_Init;
	Osc_Init.OscillatorType = RCC_OSCILLATORTYPE_LSE;
	Osc_Init.LSEState = RCC_LSE_ON;
	if (HAL_RCC_OscConfig(&Osc_Init) != HAL_OK){
		Error_handler();
	}
#endif

	HAL_RCC_MCOConfig(RCC_MCO1,RCC_MCO1SOURCE_LSE,RCC_MCODIV_1);
}



void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
    if(! is_capture_done) {
	if(count ==1){
    	 input_capture[0] = __HAL_TIM_GetCompare(htim,TIM_CHANNEL_1);
    	 count++;
     }
     else if(count ==2){
    	 input_capture[1] = __HAL_TIM_GetCompare(htim,TIM_CHANNEL_1);
    	 count == 1;
    	 is_capture_done = TRUE;
     }
    }
}
void Error_handler(void){
  __disable_irq();
  while (1){
  }

}


