/*
 * project_2560.c
 *
 * Created: 10/14/2022 1:53:00 PM
 * Author : Msi
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>

#include "LCD.h"
#include "tread.h"
#include "usart.h"
#include "btn.h"
#include "a2d.h"



#define up (PINL & 0B00000001)
#define down (PINL & 0B00000100)
#define back (PINL & 0B00001000)
#define forward (PINL & 0B00000010)

int me=1;
int op=0;
int se=0;
int fu=0;
int ch=0;
int r=0;
int sech=0;
int temp_s=1;
int time_s=1;
int chv=0;
int temp[4]={10,20,30,40};
int timer[4]={5,6,7,8};
char re;

void update_menu(int);
void update_option(int);
void update_setting(int);
void update_fun(int,int);
void run(int);
void temp_step(int);
void time_step(int);
void update_edit(int);
void temp_edit_value(int);
void timer_edit_value(int);
void SPI_Slave_Init(void);
char SPI_Slave_Receive(void);


int main(void)
{
	while(1){
		
int u=0;		
me=1;
op=0;
se=0;
fu=0;
 ch=0;
r=0;
sech=0;
 temp_s=1;
time_s=1;
 chv=0;




	initPorts();
	Lcd_init();
	initADC();
//Turn_Power_INdicator_LED_ON();
	//initUSART();
	_delay_ms(10);
	initUSART();
	update_menu(me);
     
	
	
	while (1)
	{
		
		_delay_ms(250);
		if(up){
			if((op==0) && (se==0)){      //up down in main menu
					me--;
					update_menu(me);
			}
			else if((op!=0) && (!fu)){ //up down in option menu
				    if(op==1){
						op=5;
					}	     
					op--;
					update_option(op);
			}			

			else if((se) && sech==0){      //up down in setting menu
				if(se==1){
					se=3;
				}				
				se--;
				update_setting(se);
			}
			else if((fu) && ch==0 && r==0){      //up down in fun menu
				if(fu==1){
					fu=3;
				}
				fu--;
				update_fun(op,fu);
			}
			
			else if(se==1 && (sech)){      //up vale of step size of temp
			     temp_s++;
				 _delay_ms(100);
				 temp_step(temp_s);
			}
			else if(se==2 && (sech)){      //up vale of step size of temp
				time_s++;
				_delay_ms(100);
				time_step(time_s);
			}
			
			else if((fu==2) && ch && chv==0){      //up down in edit menu
				if(ch==1){
					ch=3;
				}
				ch--;
				update_edit(ch);
			}
			
			else if(ch==1 && (chv)){      //up vale of temp
				temp[op-1]=temp[op-1]+temp_s;
				_delay_ms(100);
				temp_edit_value(op);
			}
			
			else if(ch==2 && (chv)){      //up vale of time
				timer[op-1]=timer[op-1]+time_s;
				_delay_ms(100);
				timer_edit_value(op);
			}
			
					else{
						u=1;
						break;
					}
												
						
		}
				
		else if(down){
			if((op==0) && (se==0)){  //up down in main menu
				me++;
				update_menu(me);
			}

			else if((op) && (!fu)){      //up down in option menu
				    if(op==4){
					    op=0;
				    }
				    op++;
				    update_option(op);
			}

			else if((se) && sech==0){      //up down in setting menu
				if(se==2){
					se=0;
				}		
				se++;
				update_setting(se);
			}
			
			else if((fu) && ch==0 && r==0){      //up down in fun menu
				if(fu==2){
					fu=0;
				}
				fu++;
				update_fun(op,fu);
			}									
			else if(se==1 && (sech)){      //up vale of step size of temp
				temp_s--;
				_delay_ms(100);
				temp_step(temp_s);
			}
			else if(se==2 && (sech)){      //up vale of step size of temp
				time_s--;
				_delay_ms(100);
				time_step(time_s);
			}
			
			else if((fu==2) && ch && chv==0){      //up down in edit menu
				if(ch==2){
					ch=0;
				}
				ch++;
				update_edit(ch);
			}
			else if(ch==1 && (chv)){      //up vale of temp
				temp[op-1]=temp[op-1]-temp_s;
				_delay_ms(100);
				temp_edit_value(op);
			}
			
			else if(ch==2 && (chv)){      //up vale of time
				timer[op-1]=timer[op-1]-time_s;
				_delay_ms(100);
				timer_edit_value(op);
			}
			
								else{
									u=1;
									break;
								}	
			
										
									
		}
		
		else if(forward){
			if((me==1) && (!op) && (!se)){   //go to option menu
				op++;
				update_option(op);
			}

			else if((me==2) && (!se)){   //go to settinng menu
				se++;
				update_setting(se);
			}
			
			else if((op)&& (fu==0)){   //go to fun and edit menu
				fu++;
				update_fun(op,fu);
			}
		
			else if((op)&& (fu==1) && r==0){   //go to run
			    r=1;
				run(op);
			}	
			
			else if(se==1 && sech==0 ){   //go to setting temp change
			sech++;	
			 temp_step(temp_s);
			}			

			else if(se==2 && sech==0){   //go to setting time change
				sech++;
				time_step(time_s);
			}					

			else if(fu==2 && ch==0){   //go to edit menu
				ch++;
				update_edit(ch);
			}	
			
			else if(ch==1 && chv==0){   // temp change value
				chv++;
				temp_edit_value(op);
			}	
			else if(ch==2 && chv==0){   // temp change value
				chv++;
				timer_edit_value(op);
			}
			
			else{
				
				u=1;
				break;
			}
			

				
				
	    }
		
		
		
		
		
		else if(back){
			if((op) && (fu==0)){ //back to main menu from option menu
				op=0;
				update_menu(me);
			}
			
			else if((se) && sech==0){ //back to main menu from option menu
				se=0;
				update_menu(me);
			}	

			else if((fu)&& r==0 && ch==0){ //back to option menu from fun menu
				fu=0;
				update_option(op);
			}
			else if((fu)&& r){ //back to fun menu from run
				fu=1;
				update_fun(op,fu);
				r=0;
			}

			else if((se==1) && (sech) ){ //back to setting menu from step temp
				sech=0;
				update_setting(se);
			
			}
			else if((se==2) && (sech) ){ //back to setting menu from step time
				sech=0;
				update_setting(se);
				
			}
			
			else if((ch) && (chv==0) ){ //back to edit menu from value
				ch=0;
				update_fun(op,fu);
				
			}
									
			else if((ch) && (chv) ){ //back to edit menu from value
				chv=0;
				update_edit(ch);
				
			}
			
			
			
			else{
				u=1;
				break;
			}											
			
			
		}
		
		else if(u==1){
			u=0;
			break;
		}
		
		
		
	}
			}
}

void initPorts(void)
{
	LcdDataBusDirnReg = 0xFF;
	DDRL |= 0B10001111;
	DDRB =0B11100000;
	
}

void Turn_Power_INdicator_LED_ON(void)
{
	PORTB |=0B11100000;
}

void update_menu(int me){
	switch(me){
	    case 1:	
		LCD_CmdWrite(0x01);
		display(">>Select Options");
		LCD_CmdWrite(0xC0);
		display("  Settings");
		_delay_ms(500);
		break;
		
		case 2:
		LCD_CmdWrite(0x01);
		display("  Select Options");
		LCD_CmdWrite(0xC0);
		display(">>Settings");
		_delay_ms(500);
		break;
		
		case 3:
		me=1;
		break;
		
		case 0:
		me=2;
		break;
		
		
		
		
	}

	 
}

void update_option(int op){
	LCD_CmdWrite(0x01);
	switch(op){
		case 1:
		display(">>Options 1");
		LCD_CmdWrite(0xC0);
		display("  Options 2");
// 		LCD_CmdWrite(0x94);
// 		display("  Options 3");
// 		LCD_CmdWrite(0xD4);
// 		display("  Options 4");
		_delay_ms(500);
		break;
		
		case 2:
		display("  Options 1");
		LCD_CmdWrite(0xC0);
		display(">>Options 2");
// 		LCD_CmdWrite(0x94);
// 		display("  Options 3");
// 		LCD_CmdWrite(0xD4);
// 		display("  Options 4");
		_delay_ms(500);
		break;
		
		case 3:
// 		display("  Options 1");
// 		LCD_CmdWrite(0xC0);
// 		display("  Options 2");
// 		LCD_CmdWrite(0x94);
		display(">>Options 3");
		LCD_CmdWrite(0xC0);
		display("  Options 4");
		_delay_ms(500);
		break;
		
		case 4:
// 		display("  Options 1");
// 		LCD_CmdWrite(0xC0);
// 		display("  Options 2");
//		LCD_CmdWrite(0x94);
		display("  Options 3");
		LCD_CmdWrite(0xC0);
		display(">>Options 4");
		_delay_ms(500);
		break;
		
		
		
		
		
		
	}
	
}

void update_setting(int se){
	LCD_CmdWrite(0x01);
	switch(se){
		case 1:
		display(">>Temp step size");
		LCD_CmdWrite(0xC0);
		display("  Time step size");
		_delay_ms(500);
		break;
		
		case 2:
		display("  Temp step size");
		LCD_CmdWrite(0xC0);
		display(">>Time step size");
		_delay_ms(500);
		break;
		
		default:
		se=1;
		break;
		
		

		
		
			
	}	
}

void update_fun(int op,int fu){
	LCD_CmdWrite(0x01);
	if(op==1){
		if(fu==1){
			display(">>Fun:");
			display_num(temp[0]);
			display("C ");
			display_num(timer[0]);
			display("min");
			LCD_CmdWrite(0xC0);
			display("  Edit");
			_delay_ms(500);
		}
		
		if(fu==2){
			display("  Fun:");
			display_num(temp[0]);
			display("C ");
			display_num(timer[0]);
			display("min");
			LCD_CmdWrite(0xC0);
			display(">>Edit");
			_delay_ms(500);
		}
	
		

	
  }

	else if(op==2){
		
			if(fu==1){
				display(">>Fun:");
				display_num(temp[1]);
				display("C ");
				display_num(timer[1]);
				display("min");
				LCD_CmdWrite(0xC0);
				display("  Edit");
				_delay_ms(500);
			}
			
			if(fu==2){
				display("  Fun:");
				display_num(temp[1]);
				display("C ");
				display_num(timer[1]);
				display("min");
				LCD_CmdWrite(0xC0);
				display(">>Edit");
				_delay_ms(500);
			}
		
	}

	else if(op==3){
		if(fu==1){
			display(">>Fun:");
			display_num(temp[2]);
			display("C ");
			display_num(timer[2]);
			display("min");
			LCD_CmdWrite(0xC0);
			display("  Edit");
			_delay_ms(500);
		}
		
		if(fu==2){
			display("  Fun :");
			display_num(temp[2]);
			display("C ");
			display_num(timer[2]);
			display("min");
			LCD_CmdWrite(0xC0); 
			display(">>Edit");
			_delay_ms(500);
		}
			
	
		
	}
	else if(op==4){
			if(fu==1){
				display(">>Fun:");
				display_num(temp[3]);
				display("C ");
				display_num(timer[3]);
				display("min");
				LCD_CmdWrite(0xC0);
				display("  Edit");
				_delay_ms(500);
			}
				
			if(fu==2){
				display("  Fun:");
				display_num(temp[3]);
				display("C ");
				display_num(timer[3]);
				display("min");
				LCD_CmdWrite(0xC0);
				display(">>Edit");
				_delay_ms(500);
			}
			
		}
		
			
}

void run(int op){
	int i=0;
	int off=0;
	int br=0;
	LCD_CmdWrite(0xC0);
		while(1){
			if(off==0){
			LCD_CmdWrite(0xC0);
			display("Now: ");
			display_num(temp_read());
			display("C");
			}
			if(temp_read()<temp[op-1] && off==0){
				PORTB |=0B01100000;
				_delay_ms(500);
			}

			PORTB &=0B10011111;
			_delay_ms(1);
			
			
			while(i<timer[op-1]){
				LCD_CmdWrite(0xC0);
				display("Now: ");
				display_num(temp_read());
				display("C ");
				
				if(temp_read()>temp[op-1]){
					PORTB &=0B10011111;
					_delay_ms(1000);
					//LCD_CmdWrite(0x94);
					//LCD_CmdWrite(0xC0);
					LCD_CmdWrite(0xC0);
					display("Now: ");
					display_num(temp_read());
					display("C ");
					display_num(timer[op-1]-i);
					
						
					
// 					
// 					LCD_CmdWrite(0xD4);
// 					display("ON   ");
// 					LCD_CmdWrite(0xD4);
// 					display("ON.  ");
// 					LCD_CmdWrite(0xD4);
// 					display("ON.. ");
// 					LCD_CmdWrite(0xD4);
// 					display("ON...");
// 					
					i++;
				
					
					
				}
				
				else if(temp_read()<temp[op-1]){
					
									PORTB |=0B01100000;
									_delay_ms(100);
				}
				
									
									if(back){
										 _delay_ms(250);
										br=1;
										break;
									}
				 off=1;	
			}
			//LCD_CmdWrite(0x94);
			if(off==1){
		    for(int j=0;j<7;j++){
			display("OFF  ");
		    LCD_CmdWrite(0xC0);
			display("-Take out mold-");
			_delay_ms(500);
		    LCD_CmdWrite(0xC0);
			display("                  ");
			PORTB &=0B10011111;
			br=1;
			_delay_ms(100);
			PORTB |=0B10000000;
			_delay_ms(100);
			PORTB &=0B01111111;
			_delay_ms(100);
			}
			}
			_delay_ms(100);
			PORTB |=0B10000000;
			_delay_ms(100);
			PORTB &=0B01111111;
			_delay_ms(100);
		 
		 if(back || br==1){
			 _delay_ms(250);
			 off=0;
			 fu=1;
			 r=0;
			 //br=0;
			// update_fun(op,fu);
			 break;
		 }
		 
		 		 if(back || br==1){
			 		 _delay_ms(250);
			 		 off=0;
			 		 fu=1;
			 		 r=0;
			 		 br=0;
			 		 // update_fun(op,fu);
			 		 break;}

		}
		
	return;	
}


void temp_step(int temp_s){
	if(temp_s>0){
			LCD_CmdWrite(0x01);
			display_num(temp_s);
		
	}
	
	else{
		LCD_CmdWrite(0x01);
		temp_s=1;
		display_num(temp_s);
	}
}

void time_step(int time_s){
		if(time_s>0){
			LCD_CmdWrite(0x01);
			display_num(time_s);
			
		}
		
		else{
			LCD_CmdWrite(0x01);
			time_s=1;
			display_num(time_s);
		}
	
}

void update_edit(int ch){
	LCD_CmdWrite(0x01);
	switch(ch){
		case 1:
		display(">>Temp edit");
		LCD_CmdWrite(0xC0);
		display("  Timer edit");
		_delay_ms(500);
		break;
		
		case 2:
		display("  Temp edit");
		LCD_CmdWrite(0xC0);
		display(">>Timer edit");
		_delay_ms(500);
		break;
		
		default:
		ch=1;
		break;
		
		

		
		
		
	}
}

void temp_edit_value(int op){
	if(temp[op-1]>0){
		LCD_CmdWrite(0x01);
		display_num(temp[op-1]);
		
	}
	
	else{
		LCD_CmdWrite(0x01);
		temp[op-1]=1;
		display_num(temp[op-1]);
	}	
}

void timer_edit_value(int op){
	if(timer[op-1]>0){
		LCD_CmdWrite(0x01);
		display_num(timer[op-1]);
		
	}
	
	else{
		LCD_CmdWrite(0x01);
		timer[op-1]=1;
		display_num(timer[op-1]);
	}
}

void SPI_Slave_Init(void)
{

/* Set MISO output, all others input */
DDRB = (1<<DDB4);
/* Enable SPI */
SPCR = (1<<SPE);
}

char SPI_Slave_Receive(void)
{

/* Wait for reception complete */
while(!(SPSR & (1<<SPIF)));
/* Return Data Register */
return SPDR;
}