#include "stm32f4xx.h"
//IO Modes
//Configures what mode IO pin is
typedef enum{
	GPIO_Mode_IN = 0x00,  //GPIO acts as input
	GPIO_Mode_OUT = 0x01, //GPIO acts as output
	GPIO_Mode_AF = 0x02,  //GPIO is utilized by an onboard peripheral
	GPIO_Mode_AN = 0x03  //GPIO acts as analog
} GPIOMode_TypeDef;

//Configures the output type of the pin
typedef enum{
	GPIO_OType_PP = 0x00, //Push Pull
	GPIO_OType_OD = 0x01  //Open Drain
} GPIOOType_TypeDef;

//Configures IO output speed
typedef enum{
	GPIO_Speed_2MHz = 0x00, 
	GPIO_Speed_25MHz = 0x01, 
	GPIO_Speed_50MHz = 0x02, 
	GPIO_Speed_100MHz = 0x03 
} GPIOSpeed_TypeDef;

//Configures IO pull-up/pull-down
typedef enum{
	GPIO_PuPd_NONE = 0x00, //IO is neither PU/PD
	GPIO_PuPd_UP = 0x01,   //IO is set to Pull Up
	GPIO_PuPd_DOWN = 0x02, //IO is set to Pull Down
} GPIOPUPD_TypeDef;

typedef struct{
	GPIO_TypeDef* GPIOx;
	uint32_t GPIO_PinNo;
	GPIOMode_TypeDef GPIO_Mode;
	GPIOOType_TypeDef GPIO_OType;
	GPIOSpeed_TypeDef GPIO_Speed;
	GPIOPUPD_TypeDef GPIO_PUPD;
} GPIO;

void GPIO_Init(GPIO* GPIO_Struct);
void GPIO_Write(GPIO* GPIO_Struct, uint8_t GPIO_Value);
uint8_t GPIO_Read(GPIO* GPIO_Struct);
void GPIO_Toggle(GPIO* GPIO_Struct);


