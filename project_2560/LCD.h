/*
 * LCD.h
 *
 * Created: 10/14/2022 1:55:17 PM
 *  Author: Msi
 */ 


#ifndef LCD_H_
#define LCD_H_

#define LcdDataBus PORTA
#define LcdControlBus PORTA

#define LcdDataBusDirnReg DDRA

#define LCD_RS 0
#define LCD_RW 1
#define LCD_EN 2


void LCD_CmdWrite(char cmd);
void Lcd_DataWrite(char dat);
void Lcd_init(void);
void display(char[]);

void LCD_CmdWrite(char cmd)
{
	LcdDataBus = (cmd & 0xF0);
	LcdControlBus &= ~(1<<LCD_RS);
	LcdControlBus &= ~(1<<LCD_RW);
	LcdControlBus |= (1<<LCD_EN);
	_delay_ms(1);
	LcdControlBus &= ~(1<<LCD_EN);
	_delay_ms(1);
	
	LcdDataBus = ((cmd<<4) & 0xF0);
	LcdControlBus &= ~(1<<LCD_RS);
	LcdControlBus &= ~(1<<LCD_RW);
	LcdControlBus |= (1<<LCD_EN);
	_delay_ms(1);
	LcdControlBus &= ~(1<<LCD_EN);
	_delay_ms(1);
}

void Lcd_DataWrite(char dat)
{
	LcdDataBus = (dat & 0xF0);
	LcdControlBus |= (1<<LCD_RS);
	LcdControlBus &= ~(1<<LCD_RW);
	LcdControlBus |= (1<<LCD_EN);
	_delay_ms(1);
	LcdControlBus &= ~(1<<LCD_EN);
	_delay_ms(1);
	
	LcdDataBus = ((dat<<4) & 0xF0);
	LcdControlBus |= (1<<LCD_RS);
	LcdControlBus &= ~(1<<LCD_RW);
	LcdControlBus |= (1<<LCD_EN);
	_delay_ms(1);
	LcdControlBus &= ~(1<<LCD_EN);
	_delay_ms(1);
}

void Lcd_init(void)
{
	LCD_CmdWrite(0x02);
	LCD_CmdWrite(0x28);
	LCD_CmdWrite(0x0C);
	LCD_CmdWrite(0x01);
	LCD_CmdWrite(0x80);
}

void display(char a[]){
	
	int i=0;
	while(a[i]){
		Lcd_DataWrite(a[i]);
		i++;
	}
}

void display_num(int num){
	if(((num%10000)/1000)){
		Lcd_DataWrite(((num%10000)/1000)+48);
	}
	
	Lcd_DataWrite(((num%1000)/100)+48);
		
	Lcd_DataWrite(((num%100)/10)+48);
	
	
	Lcd_DataWrite((num%10)+48);
	
	
	
}




#endif /* LCD_H_ */