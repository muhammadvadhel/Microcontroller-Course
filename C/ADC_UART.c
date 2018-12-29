#include <mega128.h>
#include <delay.h>
#include <alcd.h>
#include <stdio.h>
#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (0<<ADLAR))

unsigned char nmr_sensor;
unsigned int i, jmlh_data, adc_data;
float volt;
char text[16];

unsigned int read_adc(unsigned char adc_input){
ADMUX=adc_input | ADC_VREF_TYPE;
delay_us(10);                                     // Delay needed for the stabilization of the ADC input voltage
ADCSRA|=(1<<ADSC);                                // Start the AD conversion
while ((ADCSRA & (1<<ADIF))==0);                  // Wait for the AD conversion to complete
ADCSRA|=(1<<ADIF);
return ADCW;
}

void main(void){
DDRC=(1<<DDC7) | (1<<DDC6) | (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

DDRE=(0<<DDE7) | (0<<DDE6) | (0<<DDE5) | (0<<DDE4) | (0<<DDE3) | (0<<DDE2) | (1<<DDE1) | (0<<DDE0);
PORTE=(0<<PORTE7) | (0<<PORTE6) | (0<<PORTE5) | (0<<PORTE4) | (0<<PORTE3) | (0<<PORTE2) | (0<<PORTE1) | (1<<PORTE0);

DDRF=(0<<DDF7) | (0<<DDF6) | (0<<DDF5) | (0<<DDF4) | (0<<DDF3) | (0<<DDF2) | (0<<DDF1) | (0<<DDF0);
PORTF=(1<<PORTF7) | (1<<PORTF6) | (1<<PORTF5) | (1<<PORTF4) | (1<<PORTF3) | (1<<PORTF2) | (1<<PORTF1) | (1<<PORTF0);

// Communication Parameters: 8 Data, 1 Stop, No Parity // USART0 Receiver: On // USART0 Transmitter: On // USART0 Mode: Asynchronous // USART0 Baud Rate: 9600
UCSR0A=(0<<RXC0) | (0<<TXC0) | (0<<UDRE0) | (0<<FE0) | (0<<DOR0) | (0<<UPE0) | (0<<U2X0) | (0<<MPCM0);
UCSR0B=(0<<RXCIE0) | (0<<TXCIE0) | (0<<UDRIE0) | (1<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);
UCSR0C=(0<<UMSEL0) | (0<<UPM01) | (0<<UPM00) | (0<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00) | (0<<UCPOL0);
UBRR0H=0x00;
UBRR0L=0x40;

// ADC initialization // ADC Clock frequency: 312.500 kHz // ADC Voltage Reference: AREF pin
ADMUX=ADC_VREF_TYPE;
ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADFR) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (0<<ADPS1) | (1<<ADPS0);
SFIOR=(0<<ACME);

lcd_init(16);

while (1){
      do{                                                   //untuk menampilkan "Masukkan Nomor"
        putsf("masukkan nomor sensor (0-7): ");
        scanf("%d", &nmr_sensor);
        printf("%d\r", nmr_sensor);
        if (nmr_sensor >7) printf("input nomor sensor salah\r"); 
      }
      while(nmr_sensor>7); 
      
      do{                                                   
        putsf("Masukkan Jumlah data (0-65535): ");
        scanf("%d", &jmlh_data);
        printf("%d\r", jmlh_data);
        if (jmlh_data > 65535) printf("input jumlah data salah\r"); 
      }
      while(jmlh_data > 65535); 
      
      for (i=1; i<=jmlh_data; i++){
        adc_data = read_adc(nmr_sensor);
        printf("%d ",adc_data);
        
        volt = (float) adc_data/1024*5;
        printf("%4.2f V\r", volt);
        sprintf(text,"Data= %-4d", adc_data);
        lcd_gotoxy(0,0);
        lcd_puts(text);
        delay_ms(100);  
      };
   }
}
