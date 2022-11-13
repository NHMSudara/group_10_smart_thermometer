/*
 * btn.h
 *
 * Created: 10/14/2022 1:54:09 PM
 *  Author: Msi
 */ 

#ifndef BTN_H_
#define BTN_H_

#include "a2d.h"
int s_temp1=60;//static set
int s_tim1=6;
#define up (PINB & 0B00000001)
int s=1;

void btn_fun(void){
	if(s==1){ //highligt option
		
		LCD_CmdWrite(0x01);
		display(">>Select Options");
		LCD_CmdWrite(0xC0);
		display("Settings");
		_delay_ms(500);
		while(1){
			if((PINB & 0B00000001)||(PINB & 0B00000100)||(PINB & 0B00000010)){
				break;
			}
			
			
		}
		
		
	}

	if(((PINB & 0B00000010)&& s==1)||s==3){ //go to options
		if(s==1){
			LCD_CmdWrite(0x01);
			s=s+2;
		}
		
		
		display(">>Options 1");
		LCD_CmdWrite(0xC0);
		display("Options 2");
		LCD_CmdWrite(0x94);
		display("Options 3");
		LCD_CmdWrite(0xD4);
		display("Options 4");
		
		_delay_ms(500);
		while(1){
			if((PINB & 0B00000001)||(PINB & 0B00000100)||(PINB & 0B00000010)||(PINB & 0B00001000)){
				break;
			}
			
			
		}
	}
	//
		if(((PINB & 0B00000100) && s==3)||s==4){ ////highligt opration 2
			
			if(s==3){
				LCD_CmdWrite(0x01);
				s=s+1;
				}
				
			display("Options 1");
			LCD_CmdWrite(0xC0);
			display(">>Options 2");
			LCD_CmdWrite(0x94);
			display("Options 3");
			LCD_CmdWrite(0xD4);
			display("Options 4");
			
			_delay_ms(500);
			
			while(1){
				if((PINB & 0B00000010)||(PINB & 0B00000001 )||(PINB & 0B00001000)){
					break;
				}
			}
			
		}
		
		if(((PINB & 0B00000010)&& s==3)||s==7){ //go to options details=1
			if(s==3){
				LCD_CmdWrite(0x01);
				s=s+4;
			}
			
			
			display(">>Set_val: ");
			display_num(s_temp1);
			display("C  ");
			
			display_num(s_tim1);
			display("S");
			
			LCD_CmdWrite(0xC0);
			display("Edit");
			
			_delay_ms(500);
			while(1){
				if((PINB & 0B00000001)||(PINB & 0B00000010)||(PINB & 0B00001000)){
					break;
				}
			}
		}

	if(((PINB & 0B00000010)&& s==4)||s==12){ //go to options details=2
		if(s==4){
			LCD_CmdWrite(0x01);
			s=s+8;
		}
		
		
		display(">>Set_val: 80C 2min");
		LCD_CmdWrite(0xC0);
		display("Edit");
		
		_delay_ms(500);
		while(1){
			if((PINB & 0B00000001)||(PINB & 0B00000000)||(PINB & 0B00001000)){
				break;
			}
		}
	}


	if(((PINB & 0B00000010)&& s==7)||s==9){ //go to operating 1
		if(s==7){
			LCD_CmdWrite(0x01);
			s=s+2;
		}
		
		
		display("Set Temp: ");
		display_num(s_temp1);
		display("C");
	
		
		
		_delay_ms(500);
		int i=0;
		while(1){
			
		LCD_CmdWrite(0xC0);
		display("Now Temp: ");
		display_num(read_temp());
		display("C");
		
		if(read_temp()<s_temp1){
				PORTB |=0B01000000;
				_delay_ms(1000);
		}
		
		PORTB &=0B10111111;
		_delay_ms(1);
		
		
			while(i<s_tim1){
				LCD_CmdWrite(0xC0);
				display("Now Temp: ");
				display_num(read_temp());
				display("C");
				
				if(read_temp()>s_temp1){
							PORTB &=0B10111111;
							_delay_ms(100);
				_delay_ms(800);
				LCD_CmdWrite(0x94);
				display_num(s_tim1-i);
				
				
				
					LCD_CmdWrite(0xD4);
					display("ON   ");
					LCD_CmdWrite(0xD4);
					display("ON.  ");
					LCD_CmdWrite(0xD4);
					display("ON.. ");
					LCD_CmdWrite(0xD4);
					display("ON...");
					
					i++;
				
				
				
			}
			
			else{
				PORTB |=0B01000000;
				_delay_ms(1000);
				
			}
			
			
		}
		LCD_CmdWrite(0x94);
		display("OFF  ");
		LCD_CmdWrite(0xD4);
		display("-Take out mold-");
		_delay_ms(100);
		LCD_CmdWrite(0xD4);
		display("                  ");
		_delay_ms(100);
		PORTB |=0B10000000;
		_delay_ms(100);
		PORTB &=0B01111111;
		_delay_ms(100);
		
		
		
		
			
			
		
			
			
			if((PINB & 0B00000001)||((PINB & 0B00000100)||(PINB & 0B00001000))){
				break;
			}
		}
	}


	if((PINB & 0B00001000 ) && (s==7||s==12)){//back to option
		
		LCD_CmdWrite(0x01);
		if(s==7){
		s=s-4;}
		else if(s==12){
			s=s-8;
		}
		
		//s=1;
	}

	//

	if((PINB & 0B00001000 ) && s==9){//back to option details
		
		LCD_CmdWrite(0x01);
		s=s-2;
		//s=1;
	}
	
	if((PINB & 0B00001000 ) && (s==3||s==4)){//back to home
		
		LCD_CmdWrite(0x01);
		s=1;
	}











	if(((PINB & 0B00000100) && s==1)||s==2){ ////highligt settings
		
		LCD_CmdWrite(0x01);
		s++;
		display("Select Options");
		LCD_CmdWrite(0xC0);
		display(">>Settings");
		
		_delay_ms(500);
		
		while(1){
			if((PINB & 0B00000010)||(PINB & 0B00000001 )){
				break;
			}
		}
		
		
		
	}

	if(( up)&& s==2){//by up arrow highligt option
		
		LCD_CmdWrite(0x01);
		s--;
	}
}
#endif /* BTN_H_ */