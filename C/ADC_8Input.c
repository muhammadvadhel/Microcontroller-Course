#include <mega128.h>
#include <stdio.h>
#include <delay.h>
#include <alcd.h>
#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (0<<ADLAR))

unsigned int adc_data;
unsigned char i;
float voltage;
char text[16];

unsigned int read_adc(unsigned char adc_input){
ADMUX=adc_input | ADC_VREF_TYPE;
delay_us(10);                                                   // Delay needed for the stabilization of the ADC input voltage
ADCSRA|=(1<<ADSC);                                              // Start the AD conversion
while ((ADCSRA & (1<<ADIF))==0);                                // Wait for the AD conversion to complete
ADCSRA|=(1<<ADIF);
return ADCW;
}

void main(void){
DDRC=(1<<DDC7) | (1<<DDC6) | (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

DDRF=(0<<DDF7) | (0<<DDF6) | (0<<DDF5) | (0<<DDF4) | (0<<DDF3) | (0<<DDF2) | (0<<DDF1) | (0<<DDF0);
PORTF=(1<<PORTF7) | (1<<PORTF6) | (1<<PORTF5) | (1<<PORTF4) | (1<<PORTF3) | (1<<PORTF2) | (1<<PORTF1) | (1<<PORTF0);

ADMUX=ADC_VREF_TYPE;                // ADC Clock frequency: 312.500 kHz
ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADFR) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (0<<ADPS1) | (1<<ADPS0);
SFIOR=(0<<ACME);
lcd_init(16);

while (1){
      for (i=0; i<=7; i++){                               // i = nomor sensor
            adc_data = read_adc(i);
            sprintf(text,"Data(%d)= %4d",i, adc_data);
            lcd_gotoxy(0,0);
            lcd_puts(text);
            
            voltage = (float)adc_data/1024*5;
            sprintf(text,"Volt(%d)= %4.2f V", i, voltage);
            lcd_gotoxy(0,1);
            lcd_puts(text);
            delay_ms(100);
      }
   }
}
