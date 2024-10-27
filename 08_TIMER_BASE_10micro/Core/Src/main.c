/*
 * main.c
 *
 *  Created on: 04-Aug-2024
 *      Author: Himanshu Singh
 */


#include<string.h>
#include "stm32f4xx_hal.h"
#include"main.h"

void SystemClockConfig(uint8_t clock_freq);
void Error_handler(void);
void TIMER3_Init(void);
void GPIO_Init(void);

TIM_HandleTypeDef htimer3;

int main(void){
	HAL_Init();
	SystemClockConfig(SYS_CLOCK_FREQ_50_MHZ);
	GPIO_Init();
	TIMER3_Init();

	// lets start the timer
	HAL_TIM_Base_Start(&htimer3);
	while(1){
	}


	return 0;
}


// High Level Initialization
void TIMER3_Init(void){
	htimer3.Instance = TIM3;
	htimer3.Init.Prescaler = 9;
	htimer3.Init.Period = 50-1;
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

void SystemClockConfig(uint8_t clock_frequency){
	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;

	uint32_t FLatency = 0;
	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	osc_init.HSIState = RCC_HSI_ON;
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
    	Error_handler();
    }
    if(HAL_RCC_ClockConfig(&clk_init,FLatency) != HAL_OK){
    		Error_handler();
    }

    //Systick configuration
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
}


void Error_handler(void){
  __disable_irq();
  while (1){
  }

}


