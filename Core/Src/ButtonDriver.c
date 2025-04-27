/*
 * ButtonDriver.c
 *
 *  Created on: Apr 17, 2025
 *      Author: Ethan Edwards
 */

#include "ButtonDriver.h"

/*void InitButton()
{
	GPIO_InitTypeDef      Config;
	Config.Mode =         GPIO_MODE_INPUT;
	Config.Speed =        GPIO_SPEED_FREQ_MEDIUM;
	Config.Pull =         GPIO_NOPULL;
	Config.Pin =          BUTTON_PIN_NUM;

	__HAL_RCC_GPIOA_CLK_ENABLE();
	HAL_GPIO_Init(GPIOA, &Config);
}*/

/*bool pressButton()
{
uint8_t check = readPin(GPIOA,BUTTON_PIN_NUM);

	if(check == 1)

	{
		return true;
	}
	else
	{
		return false;
	}
}*/

void InitButtonInterrupts()
{
	    GPIO_InitTypeDef      Config;
		Config.Mode =         GPIO_MODE_IT_RISING;
		Config.Speed =        GPIO_SPEED_FREQ_MEDIUM;
		Config.Pull =         GPIO_NOPULL;
		Config.Pin =          BUTTON_PIN_NUM;

		__HAL_RCC_GPIOA_CLK_ENABLE();
		HAL_GPIO_Init(GPIOA, &Config);

		SYSCFG->EXTICR[0] |= (0x0 << (4 * BUTTON_PIN_NUM));
		EXTI->IMR |= (1 << BUTTON_PIN_NUM);
		EXTI->RTSR |= (1 << BUTTON_PIN_NUM);

		//HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

