#include "LiquidCrystal_i2c.h"
#include "i2c.h"

void lcd_init(){
	//initialization sequence comes from Hitachi HD44780 LCD datasheet
	//init starts
	send(0x30);
	delay(200);
	send(0x30);
  delay(200);	
	send(0x30);
	delay(200);
	send(0x20);
	delay(200);
	//init cmd's start here
	lcd_send_cmd(0x28); 
	delay(100);
	lcd_send_cmd(0x08);
	delay(100);
	lcd_send_cmd(0x01);
	delay(100);
	lcd_send_cmd(0x06);
	delay(100);
	lcd_send_cmd(0x00);
	delay(100);
	lcd_send_cmd(0x40);
	delay(100);
	//init ends
	//clears display
	lcd_send_cmd(0x01);
	delay(100);
	//display ON, Cursor ON, Blinking ON
	lcd_send_cmd(0x0F);
	delay(100);
}

void lcd_clear(){
	lcd_send_cmd(0x01);
	delay(200);
}

void lcd_return(){
	lcd_send_cmd(0x02);
	delay(200);
}

void lcd_setCursor(uint8_t col, uint8_t row){
	switch(row){
	case 0:
		lcd_send_cmd(0x80 | col);
		break;
	case 1:
		lcd_send_cmd(0x80 | (0x40 + col));
		break;
	}
}

void lcd_printStr(char* str){
	for(uint8_t i = 0; i < strlen(str); i++){
		lcd_send_data(str[i]);
	}
}

void lcd_printInt(int number, uint8_t number_of_digits){
	char c[number_of_digits];
	sprintf(c, "%d", number);
	lcd_printStr(c);
}

void lcd_printFloat(float number, uint8_t number_of_digits){
	char c[number_of_digits];
	snprintf(c, number_of_digits + 1, "%f", number);
	lcd_printStr(c);
}

void lcd_printCustom(uint8_t addr){
	lcd_send_data(addr & 0x7);
	delay(250);
}

void lcd_entry_mode(uint8_t inc_dec_cursor, uint8_t display_shift){
	lcd_send_cmd(0x04 | inc_dec_cursor | display_shift);
	delay(250);
}

void lcd_display_control(uint8_t display_on_off, uint8_t cursor_on_off, uint8_t cursor_blink){
	lcd_send_cmd(0x08 | display_on_off | cursor_on_off | cursor_blink);
	delay(250);
}

void lcd_cursor_display_shift(uint8_t shift_cursor_display_left_right){
	lcd_send_cmd(0x10 | shift_cursor_display_left_right);
	delay(200);
}

void lcd_function_set(uint8_t number_of_lines, uint8_t chrFont){
	lcd_send_cmd(0x20 | number_of_lines | chrFont);
	delay(200);
}

void lcd_createChar(uint8_t addr, uint8_t* data){
	lcd_send_cmd(0x40 | ((addr & 0x7) << 3));
	for(int i = 0; i < 8; i++){
		lcd_send_data(data[i]);
	}
	lcd_send_cmd(0x80);
	delay(100);
}

void lcd_send_cmd(uint8_t cmd){
	uint8_t upperNibble = cmd & 0xF0;
	uint8_t lowerNibble = (cmd << 4) & 0xF0;
	
	send(upperNibble);
	send(lowerNibble);
}

void lcd_send_data(uint8_t data){
	uint8_t upperNibble = data & 0xF0;
	uint8_t lowerNibble = (data << 4) & 0xF0;
	
	send(upperNibble | 0x01);
	send(lowerNibble | 0x01);
}

void send(uint8_t data){
	i2c_start();
	i2c_address(0x4E);
	i2c_write(data);
	delay(200);
	i2c_write(data | 0x0C);
	delay(200);
	i2c_write(data);
	delay(200);
	i2c_stop();
}

void delay(int ms){
	for(volatile int i = 0; i < ms; i++);
}
