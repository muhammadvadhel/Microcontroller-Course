#include <mega128.h>
#include <alcd.h>
#include <spi.h>
#include <delay.h>
#include <stdio.h>
#define ADC_CS PORTB.0
#define MCP3204_command 0B00000110          //0000 0|start_bit|singel|0

unsigned int data;
unsigned char no_channel;
float tegangan;
char text[16];

unsigned int read_ADC_MCP_3204(unsigned char no_sensor){
unsigned int temp1, temp2;

ADC_CS=1;
ADC_CS=0;
SPDR= MCP3204_command;

while ((SPSR & 0x80)==0);                  //tunggu disini sampe SPIF aktif (==1)
temp1=SPDR;                                //cuekkin datanya
no_sensor= no_sensor<<6;
SPDR=no_sensor;

while ((SPSR & 0x80)==0);
temp1=SPDR & 0x000F;                       //hanya butuh 4 bit terakhir
temp1= temp1<<8;                           //menempatkan 4 bit MSB di posisi yang benar
SPDR=0;

while ((SPSR & 0x80)==0);
temp2=SPDR & 0x00FF;                       //karena yang dibutuhkan hanya 8 bit terakhir
temp1= temp1 | temp2;                      //di OR kan
ADC_CS=1;
return temp1;
}

void main(void){
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0);
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (1<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

DDRC=(1<<DDC7) | (1<<DDC6) | (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// SPI initialization // SPI Type: Master // SPI Clock Rate: 625.000 kHz
// SPI Clock Phase: Cycle Start // SPI Clock Polarity: Low // SPI Data Order: MSB First
SPCR=(0<<SPIE) | (1<<SPE) | (0<<DORD) | (1<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (1<<SPR0);
SPSR=(0<<SPI2X);

lcd_init(16);

while (1){
      for (no_channel=0; no_channel<=3; no_channel++){
        data= read_ADC_MCP_3204(no_channel);
        sprintf(text,"Data(%d)= %d",no_channel,data);
        lcd_gotoxy(0,0);
        lcd_puts(text);
        
        tegangan= (float) data/4096*5.0;  
        sprintf(text,"Volt(%d)= %5.3f V",no_channel,tegangan);
        lcd_gotoxy(0,1);
        lcd_puts(text);
        delay_ms(100);        
      }
   }
}