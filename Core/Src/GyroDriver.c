/*
 * GyroDriver.c
 *
 *  Created on: Apr 17, 2025
 *      Author: Ethan Edwards
 */
#include "GyroDriver.h"

static HAL_StatusTypeDef status;
static SPI_HandleTypeDef SPI5_Def;


void GyroInit()
{
	 __HAL_RCC_SPI5_CLK_ENABLE();

	SPI5_Def.Instance = SPI5;
	SPI5_Def.Init.Mode = SPI_MODE_MASTER;
	SPI5_Def.Init.Direction = SPI_DIRECTION_2LINES;
	SPI5_Def.Init.DataSize = SPI_DATASIZE_8BIT;
	SPI5_Def.Init.CLKPolarity = SPI_POLARITY_LOW;
	SPI5_Def.Init.CLKPhase = SPI_PHASE_1EDGE;

	status = HAL_SPI_Init(&SPI5_Def);
	GyroHalVerify();
	__HAL_SPI_ENABLE(&SPI5_Def);

	__HAL_RCC_GPIOF_CLK_ENABLE();
	GPIO_InitTypeDef SelectSPI;
	SelectSPI.Mode =         GPIO_MODE_AF_PP;
	SelectSPI.Speed =        GPIO_SPEED_FREQ_MEDIUM;
	SelectSPI.Alternate =    GPIO_AF5_SPI5;
	SelectSPI.Pull =         GPIO_NOPULL;
	SelectSPI.Pin =          GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;

	HAL_GPIO_Init(GPIOF,&SelectSPI);

	GPIO_InitTypeDef ChipSelect;
	ChipSelect.Mode = GPIO_MODE_OUTPUT_PP;
	ChipSelect.Speed = GPIO_SPEED_FREQ_MEDIUM;
	ChipSelect.Pull = GPIO_NOPULL;
	ChipSelect.Pin = GPIO_PIN_1;

	HAL_GPIO_Init(GPIOF, &ChipSelect);

	GyroCommDisable();

}

void GyroID()
{
	uint8_t gyro_id = GyroRegRead(WHO_AM_I);
	printf("Gyro ID: 0x%02X\n", gyro_id);
}


void GyroPower()
{
	GyroRegWrite(CTRL_REG1, GYRO_POWER_ON);
}

void GyroTempGet()
{
	uint8_t temp_data = GyroRegRead(OUT_TEMP);
	printf("Temperature Change: %d\n", temp_data);
}



void GyroRegConfig()
{
	GyroRegWrite(CTRL_REG5, GYRO_BOOT);
}


uint8_t GyroRegRead(uint8_t address)
{
	uint8_t data[2];
	uint8_t return_data[2];
	data[0] = address | (1 << BIT_SET_FOR_READ);
	data[1] = 0x0; // dummy data

	GyroCommEnable();
	status = HAL_SPI_TransmitReceive(&SPI5_Def, data, return_data, 2, 100);
	GyroCommDisable();

	uint8_t output = return_data[1];
	return output;
}

void GyroRegWrite(uint8_t regAddress, uint8_t write_data)
{
	uint8_t data[2];
	data[0] = regAddress & ~(1 << BIT_SET_FOR_READ);
	data[1] = write_data;

	GyroCommEnable();
	status = HAL_SPI_Transmit(&SPI5_Def, data, 2, 100);
	GyroCommDisable();

}


void GyroHalVerify()
{
	Application_Assert(status == HAL_OK);
}

void GyroCommEnable()
{
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, GPIO_PIN_RESET);
}

void GyroCommDisable()
{
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, GPIO_PIN_SET);
}
