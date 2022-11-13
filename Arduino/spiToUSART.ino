
// this example is public domain. enjoy!
// https://learn.adafruit.com/thermocouple/

#include "max6675.h"

int thermoDO = 7;
int thermoCS = 5;
int thermoCLK = 6;

int tempc=0;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {
  Serial.begin(9600);


  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {
  // basic readout test, just print the current temp
  
tempc=thermocouple.readCelsius();
 Serial.write((tempc%10000)/1000+48);
 Serial.write((tempc%1000)/100+48);
  Serial.write((tempc%100)/10+48);
   Serial.write((tempc%10)+48);
   Serial.write(10);
 
   // For the MAX6675 to update, you must delay AT LEAST 250ms between reads!
   delay(500);
}



   

  
  
 
  
  
