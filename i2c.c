#include "i2c.h"

void i2c_cfg(){
	//cfg
	I2C1->CR2 |= 16;
	I2C1->CCR |= 250;
	I2C1->TRISE |= 51;
	I2C1->CR1 |= 1;
}

void i2c_start(){
	I2C1->CR1 |= (1 << 8);
	while(!(I2C1->SR1 & 1));
}

void i2c_write(uint8_t data){
	while(!(I2C1->SR1 & (1 << 7)));
	I2C1->DR = data;
	while(!(I2C1->SR1 & (1 << 2)));
}

void i2c_address(uint8_t addr){
	I2C1->DR = addr;
	while (!(I2C1->SR1 & 2));
	uint8_t temp = I2C1->SR1 | I2C1->SR2; //dummy read to clear Status Registers
}

void i2c_stop(){
	I2C1->CR1 |= (1<<9);
}
