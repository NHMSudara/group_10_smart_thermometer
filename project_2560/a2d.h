/*
 * a2d.h
 *
 * Created: 10/14/2022 2:56:15 PM
 *  Author: Msi
 */ 


#ifndef A2D_H_
#define A2D_H_
int a_out=0;

void initADC(void){
	ADCSRA |= (1<<ADEN);
	ADCSRA |= 0B00000111;
	ADCSRA |= (1<<ADSC);
}

int readADC(uint8_t adc_input_pin){
	ADMUX = (ADMUX & 0xF0) | adc_input_pin;
	ADMUX &= 0X0B00111111;
	ADCSRA |= (1<<ADSC);
	
	while(ADCSRA & (1<<ADSC));
	
	return ADC;
}

int read_temp(void){
	a_out=((readADC(0)-98)*0.2991);

	
	return 	a_out;
}




#endif /* A2D_H_ */