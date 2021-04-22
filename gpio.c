#include "gpio.h"

void GPIO_Init(GPIO* GPIO_Struct){
	GPIO_Struct->GPIOx->MODER |= (GPIO_Struct->GPIO_Mode << (GPIO_Struct->GPIO_PinNo*2));
	if(GPIO_Struct->GPIO_Mode == GPIO_Mode_IN){
		GPIO_Struct->GPIOx->OTYPER |= (GPIO_Struct->GPIO_OType << GPIO_Struct->GPIO_PinNo);
		GPIO_Struct->GPIOx->OSPEEDR |= (GPIO_Struct->GPIO_Speed << (GPIO_Struct->GPIO_PinNo*2));
	}
	GPIO_Struct->GPIOx->PUPDR |= (GPIO_Struct->GPIO_PUPD << (GPIO_Struct->GPIO_PinNo*2)); 
}

void GPIO_Write(GPIO* GPIO_Struct, uint8_t GPIO_Value){
	if(GPIO_Value){
		GPIO_Struct->GPIOx->BSRR |= (1 << GPIO_Struct->GPIO_PinNo);
	}
	else{
		GPIO_Struct->GPIOx->BSRR |= (1 << (GPIO_Struct->GPIO_PinNo + 16));
	}
}

uint8_t GPIO_Read(GPIO* GPIO_Struct){
	if(GPIO_Struct->GPIO_Mode == GPIO_Mode_IN){
		return ((GPIO_Struct->GPIOx->IDR >> GPIO_Struct->GPIO_PinNo) & 0x01);
	}
	else if (GPIO_Struct->GPIO_Mode == GPIO_Mode_OUT){
		return ((GPIO_Struct->GPIOx->ODR >> GPIO_Struct->GPIO_PinNo) & 0x01);
	}
	return 0;
}

void GPIO_Toggle(GPIO* GPIO_Struct){
	GPIO_Struct->GPIOx->ODR ^= (1 << GPIO_Struct->GPIO_PinNo);
}
