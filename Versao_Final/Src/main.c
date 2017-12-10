/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "adc.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"


/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include <OledChar.h>
#include <OledDriver.h>
#include <OledGrph.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
extern const char tabelaad[4096][5];
int R_fixa = 220;        // Resistência fixa do divisor de tensão
int leitura = 0;           // Armazena o valor lido pela entrada analógica (valor entre 0 e 4096)
int resultado = 0;
int Vx=0;
char string_r[20];
bool btn_1 = false;
bool btn_2 = false;
bool btn_3 = false;

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_ADC1_Init();
  MX_SPI1_Init();

  /* USER CODE BEGIN 2 */
  OledInit();
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1); // Inicializa os timers para geração da PWM nos pinos A8, A9, A10
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 870);
  HAL_Delay(2000);
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 1300);
  HAL_Delay(2000);
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 1300);
  HAL_Delay(2000);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
	  int duas_casas=0;
	  int tres_casas=0;
	  int quatro_casas=0;
	  int resultado = 0;

	  HAL_ADC_Start(&hadc1);
	  OledSetCursor(0,0);
	  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)){
		  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 150);
		  OledClear();
		  OledSetCursor(0,0);
		  OledPutString("Caixa 1 aberta");
		  HAL_Delay(1000);
		  btn_1 = true;
		  while(btn_1){
			  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)==GPIO_PIN_SET){
				  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 870);
				  HAL_Delay(1000);
				  btn_1 = false;
				  OledClear();
			  }
		  }
	  }
	  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)){
		  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 480);
		  OledClear();
		  OledSetCursor(0,0);
		  OledPutString("Caixa 2 aberta");
		  HAL_Delay(1000);
		  btn_2 = true;
	  	  while(btn_2){
	  		  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)){
	  			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 1300);
	  			HAL_Delay(1000);
	  			btn_2 = false;
	  			OledClear();
	  		  }
	  	  }
	  }
	  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)){
		  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 150);
		  OledClear();
		  OledSetCursor(0,0);
		  OledPutString("Caixa 3 aberta");
		  HAL_Delay(1000);
		  btn_3 = true;
	  	  while(btn_3){
	  		  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)){
	  			  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 1300);
	  			  HAL_Delay(1000);
	  			  btn_3 = false;
	  			  OledClear();
	  		  }
	  	  }
	  }
	  int leitura = HAL_ADC_GetValue(&hadc1); //pino A6
	  char tensao[4] = {tabelaad[leitura][0],tabelaad[leitura][1],tabelaad[leitura][2],tabelaad[leitura][3]};
	  int Vx = atoi(tensao);
	  resultado = (int)(((3420*R_fixa)/Vx) - R_fixa);
	  duas_casas = (int)(resultado -(resultado*10/100));
	  tres_casas = (int)(resultado + (resultado*10/100));
	  quatro_casas = (int)(resultado +(resultado*20/100));
	  if ((resultado > 0) & (resultado < 2000)){
		  OledPutString("Resistencia: ");
		  if ((resultado > 0) & (resultado < 100)){
			  sprintf(string_r,"%d",duas_casas);
			  OledSetCursor(0,2);
			  OledPutString(string_r);
			  OledPutString(" Ohms");
			  if((resultado > 0) & (resultado < 15)){
				  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 150);
				  OledClear();
				  OledSetCursor(0,0);
				  OledPutString("Caixa 1 aberta");
				  OledSetCursor(0,2);
				  OledPutString(string_r);
				  btn_1 = true;
				  HAL_Delay(1000);
				  while(btn_1){
					  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)){
						  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 870);
						  HAL_Delay(1000);
						  btn_1 = false;
						  OledClear();
					  }
				  }
			  }
		  	}
		  if ((resultado >= 100) & (resultado < 1000)){
			  sprintf(string_r,"%d",tres_casas);
			  OledSetCursor(0,2);
			  OledPutString(string_r);
			  OledPutString(" Ohms");
			  if((resultado >260) & (resultado < 350)){
				  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 480);
				  OledClear();
				  OledSetCursor(0,0);
				  OledPutString("Caixa 2 aberta");
				  OledSetCursor(0,2);
				  OledPutString(string_r);
				  btn_2 = true;
				  HAL_Delay(1000);
				  while(btn_2){
					  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)){
						  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 1300);
						  HAL_Delay(1000);
						  btn_2 = false;
						  OledClear();
					  }
				  }
			  }
		  }
		  if ((resultado >= 1000) & (resultado < 10000)){
			  sprintf(string_r,"%d",quatro_casas);
			  OledSetCursor(0,2);
			  OledPutString(string_r);
			  OledPutString(" Ohms");
			  if((quatro >=1000) & (resultado <= 1400)){
				  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 150);
				  OledClear();
				  OledSetCursor(0,0);
				  OledPutString("Caixa 3 aberta");
				  OledSetCursor(0,2);
				  OledPutString(string_r);
				  btn_3 = true;
				  HAL_Delay(1000);
				  while(btn_3){
					  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)){
						  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 1300);
						  HAL_Delay(1000);
						  btn_3 = false;
						  OledClear();
					  }
				  }
			  }
		  }
	  //		  sprintf(string_r,"%d",resultado);
	  //		  OledSetCursor(0,2);
	  //		  OledPutString(string_r);

	  } else
		  OledPutString("Circuito aberto");
	  HAL_Delay(1000);
	  OledClear();



  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
