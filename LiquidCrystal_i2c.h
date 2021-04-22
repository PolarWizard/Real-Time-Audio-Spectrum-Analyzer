//liquid crystal display library with i2c module
// D7 D6 D5 D4 x E RW RS
//|-----1-----|2|---3---|
//1. Data lines, i2c only allows for 4 data lines to be hooked up
//meaning that the lcd can only operate in 4bit mode, lower 4 bits
//are never used
//2. x = dont care, this bit is not hooked up to anything and can be
//either a 0 or 1
//3. Going from left to right we have E: the pulse signal,
//RW: read/write, 0 for write, 1 for read, and RS: Register Select,
//0 for sending commands and 1 for sending data to CG/DD RAM

#include "stm32f4xx.h"
#include <stdio.h>
#include <string.h>

//display controls
#define DISPLAY_ON  		 		 0x04
#define DISPLAY_OFF 		 		 0x00
#define CURSOR_ON   		 		 0x02
#define CURSOR_OFF  		 		 0x00
#define CURSOR_BLINK_ON  	 	 0x01
#define CURSOR_BLINK_OFF 		 0x00
//function set
//display settings
#define TWO_LINE       		 	 0x08
#define ONE_LINE        		 0x00
#define FONT_5x10        		 0x04
#define FONT_5x8         		 0x00
//cursor or display shift
//happens only when cmd is sent
#define SHIFT_DISPLAY_LEFT   0x08
#define SHIFT_DISPLAY_RIGHT  0x0C
#define SHIFT_CURSOR_LEFT		 0x00
#define SHIFT_CURSOR_RIGHT   0x04
//entry mode set
//happens only after ram r/w
#define INC_CURSOR_DIRECTION 0x02
#define DEC_CURSOR_DIRECTION 0x+00
#define DISPLAY_SHIFT_ON		 0x01
#define DISPLAY_SHIFT_OFF		 0x00

//Use these:
//----high level abstraction----
void lcd_init(void);
void lcd_clear(void);
void lcd_return(void);
void lcd_setCursor(uint8_t col, uint8_t row); //col: 0-15, row: 0-1
void lcd_printStr(char* str);
void lcd_printInt(int number, uint8_t number_of_digits);
void lcd_printFloat(float number, uint8_t number_of_digits);
void lcd_printCustom(uint8_t addr);
void lcd_createChar(uint8_t addr, uint8_t* data);
//lcd settings
void lcd_entry_mode(uint8_t inc_dec_cursor, uint8_t display_shift);
void lcd_display_control(uint8_t display_on_off, uint8_t cursor_on_off, uint8_t cursor_blink);
void lcd_cursor_display_shift(uint8_t shift_cursor_display_left_right);
void lcd_function_set(uint8_t number_of_lines, uint8_t chrFont);


//Dont use these:
//----lcd level abstraction----
void lcd_send_cmd(uint8_t cmd);
void lcd_send_data(uint8_t data);

//----i2c level abstraction----
void send(uint8_t data);

//----just a "bad" delay----
void delay(int ms);
