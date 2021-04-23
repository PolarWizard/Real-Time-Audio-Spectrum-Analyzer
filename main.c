#include "stm32f4xx.h"
#include "fix_fft.h"
#include <math.h>
#include "gpio.h"
#include "i2c.h"
#include "LiquidCrystal_i2c.h"

#define samples 256

//function headers
void gpio_cfg(GPIO* i2c_SCL, GPIO* i2c_SDA, GPIO* adcInput);

void gpio_cfg(GPIO* i2c_SCL, GPIO* i2c_SDA, GPIO* adcInput){
	adcInput->GPIOx = GPIOA;
	adcInput->GPIO_PinNo = 0;
	adcInput->GPIO_Mode = GPIO_Mode_AN;
	adcInput->GPIO_PUPD = GPIO_PuPd_NONE;
	i2c_SCL->GPIOx = GPIOB;
	i2c_SCL->GPIO_PinNo = 6;
	i2c_SCL->GPIO_Mode = GPIO_Mode_AF;
	i2c_SCL->GPIO_OType = GPIO_OType_OD;
	i2c_SCL->GPIO_Speed = GPIO_Speed_100MHz;
	i2c_SCL->GPIO_PUPD = GPIO_PuPd_UP;
	i2c_SDA->GPIOx = GPIOB;
	i2c_SDA->GPIO_PinNo = 7;
	i2c_SDA->GPIO_Mode = GPIO_Mode_AF;
	i2c_SDA->GPIO_OType = GPIO_OType_OD;
	i2c_SDA->GPIO_Speed = GPIO_Speed_100MHz;
	i2c_SDA->GPIO_PUPD = GPIO_PuPd_UP;
	GPIOB->AFR[0] |= (4 << 24) | (4 << 28);
}

uint16_t mySqrt(uint32_t number)
{
    uint16_t res=0;
    uint16_t add= 0x8000;   
    int i;
    for(i=0;i<16;i++)
    {
        uint16_t temp=res | add;
        uint32_t g2=temp*temp;      
        if (number>=g2)
        {
            res=temp;           
        }
        add>>=1;
    }
    return res;
}

void print_Bands(int* band){
	for(int i = 0; i < 16; i++){
		lcd_setCursor(i, 1);
		if(band[i] < 35){
			lcd_printCustom(0);
			lcd_setCursor(i, 0);
			lcd_printStr(" ");
		}
		else if(band[i] < 45){
			lcd_printCustom(1);
			lcd_setCursor(i, 0);
			lcd_printStr(" ");
		}
		else if(band[i] < 50){
			lcd_printCustom(2);
			lcd_setCursor(i, 0);
			lcd_printStr(" ");
		}
		else if(band[i] < 52){
			lcd_printCustom(3);
			lcd_setCursor(i, 0);
			lcd_printStr(" ");
		}
		else if(band[i] < 54){
			lcd_printCustom(4);
			lcd_setCursor(i, 0);
			lcd_printStr(" ");
		}
		else if(band[i] < 56){
			lcd_printCustom(5);
			lcd_setCursor(i, 0);
			lcd_printStr(" ");
		}
		else if(band[i] < 58){
			lcd_printCustom(6);
			lcd_setCursor(i, 0);
			lcd_printStr(" ");
		}
		else if(band[i] < 60){
			lcd_printCustom(7);
			lcd_setCursor(i, 0);
			lcd_printStr(" ");
		}
		else if(band[i] < 62){
			lcd_printCustom(7);
			lcd_setCursor(i, 0);
			lcd_printCustom(1);
		}
		else if(band[i] < 63){
			lcd_printCustom(7);
			lcd_setCursor(i, 0);
			lcd_printCustom(2);
		}
		else if(band[i] < 64){
			lcd_printCustom(7);
			lcd_setCursor(i, 0);
			lcd_printCustom(3);
		}
		else if(band[i] < 65){
			lcd_printCustom(7);
			lcd_setCursor(i, 0);
			lcd_printCustom(4);
		}
		else if(band[i] < 66){
			lcd_printCustom(7);
			lcd_setCursor(i, 0);
			lcd_printCustom(5);
		}
		else if(band[i] < 67){
			lcd_printCustom(7);
			lcd_setCursor(i, 0);
			lcd_printCustom(6);
		}
		else{
			lcd_printCustom(7);
			lcd_setCursor(i, 0);
			lcd_printCustom(7);
		}
	}
	
}

int main(){
	uint8_t data0[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F};
	uint8_t data1[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x1F};
	uint8_t data2[8] = {0x00,0x00,0x00,0x00,0x00,0x1F,0x1F,0x1F};
	uint8_t data3[8] = {0x00,0x00,0x00,0x00,0x1F,0x1F,0x1F,0x1F};
	uint8_t data4[8] = {0x00,0x00,0x00,0x1F,0x1F,0x1F,0x1F,0x1F};
	uint8_t data5[8] = {0x00,0x00,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F};
	uint8_t data6[8] = {0x00,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F};
	uint8_t data7[8] = {0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F};
	RCC->AHB1ENR |= 0x9F; //Initialize clks for all GPIO's
	RCC->APB2ENR |= (1 << 8); //enable ADC1 clk
	RCC->APB1ENR |= (7 << 21); //enable ALL I2C clks
	
	GPIO in, i2c_SCL, i2c_SDA, adcInput;
	gpio_cfg(&i2c_SCL, &i2c_SDA, &adcInput);
	GPIO_Init(&adcInput); //A1, ADC1 channel 1
	GPIO_Init(&i2c_SCL);
	GPIO_Init(&i2c_SDA);
	i2c_cfg();
	lcd_init();
	lcd_display_control(DISPLAY_ON, CURSOR_OFF, CURSOR_BLINK_OFF);
	lcd_createChar(0, data0);
	lcd_createChar(1, data1);
	lcd_createChar(2, data2);
	lcd_createChar(3, data3);
	lcd_createChar(4, data4);
	lcd_createChar(5, data5);
	lcd_createChar(6, data6);
	lcd_createChar(7, data7);
	//adc cfg
	ADC1->CR1 |= (0 << 24); //12 bits of resolution
	ADC1->CR2 |= (1 << 1);
	ADC1->SMPR2 |= 0; //sampling time 144 cycles
	ADC1->CR2 |= 1; //ADC ON
	ADC1->CR2 |= (1 << 30); //start conversion
	for(volatile int i = 0; i < 100000; i++); //stabilize clk
	short real_sample[samples] = {0};
	short imag_sample[samples] = {0};
	int band[16] = {0};
	while(1){
		for(int i = 0; i < samples; i++){
			real_sample[i] = (uint32_t)(ADC1->DR - 2240) << 4;
			for(volatile int j = 0; j < 100; j++);
		}
		fix_fft(real_sample, imag_sample, 8, 0);
		for(int cnt = 0; cnt < 16; cnt++){
			for(int i = cnt*8; i < (cnt*8 + 8); i++){
				band[cnt] += real_sample[i] * real_sample[i] + imag_sample[i] * imag_sample[i];
			}
			band[cnt] = mySqrt(band[cnt] >> 3);
			band[cnt] = 20.0f*log10f(band[cnt]);
		}
		print_Bands(band);
		lcd_return();
		for(int i = 0; i < 16; i++){
			band[i] = 0;
		}
	}
}
