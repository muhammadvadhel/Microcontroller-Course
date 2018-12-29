/*******************************************************
Project : Biner to BCD
Version : 1.1
Date    : 9/21/2018
Author  : Mr. Muhammad
Company : Department Physics University of Indonesia
Comments:

Chip type               : ATmega128
Program type            : Application
AVR Core Clock frequency: 10.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 1024
*******************************************************/

#include <mega128.h>
#include <bcd.h>

signed char counter = 0;

char bcd27segment(char y)
{
char data7segment;
switch (y) {
    case 0 :
            data7segment = 0xC0;
            break;
    case 1 :
            data7segment = 0xF9;
            break;
    case 2 :
            data7segment = 0xA4;
            break;
    case 3 :
            data7segment = 0xB0;
            break;
    case 4 :
            data7segment = 0x99;
            break;
    case 5 :
            data7segment = 0x92;
            break;
    case 6 :
            data7segment = 0x82;
            break;
    case 7 :
            data7segment = 0xF8;
            break;
    case 8 :
            data7segment = 0x80;
            break;
    case 9 :
            data7segment = 0x90;
            break;       
    default:
            data7segment = 0xFF;
    };
    return(data7segment);
}

void display(unsigned char x)
{
char bcddata8bit, bcddata4bit, segmentdata; // lokal variabel

bcddata8bit = bin2bcd(x);                   // ubah biner ke BCD
bcddata4bit = bcddata8bit & 0x0F;           // ambil 4 bit bcd terbawah
segmentdata = bcd27segment(bcddata4bit);    // ubah bcd 4 bit ke seven segment
PORTF = segmentdata;                        // tampilkan di port F
bcddata8bit = bcddata8bit>>4;               // angka puluhan digeser 4 kali ke kanan
bcddata4bit = bcddata8bit & 0x0F;           // ekstrak 4 bit bcd atas
segmentdata = bcd27segment(bcddata4bit);    // ubah bcd 4 bit ke seven segment
PORTE = segmentdata;                        // tampilkan di port E
}

interrupt [EXT_INT0] void ext_int0_isr(void)
{
counter++;                                  // counter = counter + 1
if (counter > 99){
    counter = 99;
    };
display(counter);                           // jalankan sub program display
}

interrupt [EXT_INT1] void ext_int1_isr(void)
{
counter--;                                  // counter = counter - 1
if (counter <= 0){
    counter = 0;
    };
display(counter);
}

void main(void)
{
// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=P Bit0=P 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (1<<PORTD1) | (1<<PORTD0);

// Port E initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRE=(1<<DDE7) | (1<<DDE6) | (1<<DDE5) | (1<<DDE4) | (1<<DDE3) | (1<<DDE2) | (1<<DDE1) | (1<<DDE0);
// State: Bit7=1 Bit6=1 Bit5=1 Bit4=1 Bit3=1 Bit2=1 Bit1=1 Bit0=1 
PORTE=(1<<PORTE7) | (1<<PORTE6) | (1<<PORTE5) | (1<<PORTE4) | (1<<PORTE3) | (1<<PORTE2) | (1<<PORTE1) | (1<<PORTE0);

// Port F initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRF=(1<<DDF7) | (1<<DDF6) | (1<<DDF5) | (1<<DDF4) | (1<<DDF3) | (1<<DDF2) | (1<<DDF1) | (1<<DDF0);
// State: Bit7=1 Bit6=1 Bit5=1 Bit4=1 Bit3=1 Bit2=1 Bit1=1 Bit0=1 
PORTF=(1<<PORTF7) | (1<<PORTF6) | (1<<PORTF5) | (1<<PORTF4) | (1<<PORTF3) | (1<<PORTF2) | (1<<PORTF1) | (1<<PORTF0);

EICRA=(0<<ISC31) | (0<<ISC30) | (0<<ISC21) | (0<<ISC20) | (1<<ISC11) | (0<<ISC10) | (1<<ISC01) | (0<<ISC00);
EICRB=(0<<ISC71) | (0<<ISC70) | (0<<ISC61) | (0<<ISC60) | (0<<ISC51) | (0<<ISC50) | (0<<ISC41) | (0<<ISC40);
EIMSK=(0<<INT7) | (0<<INT6) | (0<<INT5) | (0<<INT4) | (0<<INT3) | (0<<INT2) | (1<<INT1) | (1<<INT0);
EIFR=(0<<INTF7) | (0<<INTF6) | (0<<INTF5) | (0<<INTF4) | (0<<INTF3) | (0<<INTF2) | (1<<INTF1) | (1<<INTF0);

// Global enable interrupts
#asm("sei")

display(counter);

while (1)
      {
      }
}
