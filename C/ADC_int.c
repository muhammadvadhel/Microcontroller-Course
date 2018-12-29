#include <mega128.h>
#include <delay.h>
#include <alcd.h>
#include <stdio.h>
#define FIRST_ADC_INPUT 0
#define LAST_ADC_INPUT 7
#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (0<<ADLAR))

unsigned int adc_data[LAST_ADC_INPUT-FIRST_ADC_INPUT+1];
float tegangan;
char text[16];

interrupt [ADC_INT] void adc_isr(void){                         // ADC interrupt service routine with auto input scanning
static unsigned char input_index=0;
adc_data[input_index]=ADCW;                                     // Read the AD conversion result
sprintf(text,"Data(%d)= %4d",input_index, adc_data[input_index]);
lcd_gotoxy(0,0);
lcd_puts(text);

tegangan = (float)adc_data[input_index]/1024*5;
sprintf(text,"Volt(%d)= %4.2f V", input_index, tegangan);
lcd_gotoxy(0,1);
lcd_puts(text);
delay_ms(100); 

if (++input_index > (LAST_ADC_INPUT-FIRST_ADC_INPUT))           // Select next ADC input
   input_index=0;
   
ADMUX=(FIRST_ADC_INPUT | ADC_VREF_TYPE)+input_index;
delay_us(10);                                                   // Delay needed for the stabilization of the ADC input voltage
ADCSRA|=(1<<ADSC);                                              // Start the AD conversion
}

void main(void){
DDRC=(1<<DDC7) | (1<<DDC6) | (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

DDRF=(0<<DDF7) | (0<<DDF6) | (0<<DDF5) | (0<<DDF4) | (0<<DDF3) | (0<<DDF2) | (0<<DDF1) | (0<<DDF0);
PORTF=(1<<PORTF7) | (1<<PORTF6) | (1<<PORTF5) | (1<<PORTF4) | (1<<PORTF3) | (1<<PORTF2) | (1<<PORTF1) | (1<<PORTF0);

ADMUX=FIRST_ADC_INPUT | ADC_VREF_TYPE;                          // ADC Clock frequency: 312.500 kHz // ADC Voltage Reference: AREF pin
ADCSRA=(1<<ADEN) | (1<<ADSC) | (0<<ADFR) | (0<<ADIF) | (1<<ADIE) | (1<<ADPS2) | (0<<ADPS1) | (1<<ADPS0);
SFIOR=(0<<ACME);

lcd_init(16);

#asm("sei")

while (1){
      
      }
}
