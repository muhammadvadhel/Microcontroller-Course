#include <mega128.h>
#include <alcd.h>
#include <stdio.h>
#include <delay.h>

unsigned char key,digit;
char text[16];

unsigned char read_keypad(void){
    unsigned char key_index;
    PORTD=0xFF;
    PORTD.4=0;
    key_index= (~PIND) & 0x0F;
    switch (key_index){
        case 1: return key=1;
            break;
        case 2: return key=4;
            break;
        case 4: return key=7;
            break;
        case 8: return key=10;          //10 itu bintang
            break;
    };
    
    PORTD.4=1; PORTD.5=0;
    key_index= (~PIND) & 0x0F;
    switch (key_index){
        case 1: return key=2;
            break;
        case 2: return key=5;
            break;
        case 4: return key=8;
            break;
        case 8: return key=0;
            break;
    };
    
    PORTD.5=1; PORTD.6=0;
    key_index= (~PIND) & 0x0F;
    switch (key_index){
        case 1: return key=3;
            break;
        case 2: return key=6;
            break;
        case 4: return key=9;
            break;
        case 8: return key=11;
            break;
    }; 

    PORTD.6=1; PORTD.7=0;
    key_index= (~PIND) & 0x0F;
    switch (key_index){
        case 1: return key=12;
            break;
        case 2: return key=13;
            break;
        case 4: return key=14;
            break;
        case 8: return key=15;
            break;
        default: return key=16;
            break;
    };
}

void main(void){
DDRA=(1<<DDA7) | (1<<DDA6) | (1<<DDA5) | (1<<DDA4) | (1<<DDA3) | (1<<DDA2) | (1<<DDA1) | (1<<DDA0);
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

DDRC=(1<<DDC7) | (1<<DDC6) | (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

DDRD=(1<<DDD7) | (1<<DDD6) | (1<<DDD5) | (1<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
PORTD=(1<<PORTD7) | (1<<PORTD6) | (1<<PORTD5) | (1<<PORTD4) | (1<<PORTD3) | (1<<PORTD2) | (1<<PORTD1) | (1<<PORTD0);

lcd_init(16);

while (1){
      do{
        digit= read_keypad();
        sprintf(text,"%d",digit);
        lcd_puts(text);
      }
        while(digit>=16);
   }
}
