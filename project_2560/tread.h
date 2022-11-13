#ifndef TREAD_H_
#define TREAD_H_

#include "usart.h"
char a='h';
char temD[20];
int i;

int c=0;
int i;
int sum=0;

int temp_read(void)
{
	initUSART();

	while (1)
	{
		sum=0;
		c=0;
		i=0;
		while(1){
			a=USART_Receive();
			if(a==' ' && a==10){
				break;
			}
			temD[i]=a;
			
			if(temD[i]==10){
				break;
			}
			if(i==0 && temD[i]>48){
				sum+=( temD[i]-48)*1000;
				c++;
			}
			
			else if(i==1&& temD[i]>48)
			{
				sum+=( temD[i]-48)*100;
				c++;
			}
			
			else if(i==2&& temD[i]>48)
			{
				sum+=( temD[i]-48)*10;
				c++;
			}
			
			else if(i==3 && temD[i]>48)
			{
				sum+=( temD[i]-48);
				c++;
			}
			i++;
			
		}
		//if(c==4){
		transmitUSART((sum%10000)/1000+48);
		transmitUSART((sum%1000)/100+48);
		transmitUSART((sum%100)/10+48);
		transmitUSART((sum%10)+48);
	    transmitUSART(10);
		if(sum>0){
		return sum;}
		//}
	
}

sum=0;
c=0;
}




#endif
