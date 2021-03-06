#include <mega128.h>
#include <alcd.h>
#include <delay.h>
#include <stdio.h>

char text[16];
char textfis[16] = {20,20,20,'V','A','D','H','E','L','-','-','U','I',20,20,20};
unsigned char i;
unsigned int counter = 0;

interrupt [EXT_INT0] void ext_int0_isr(void){
counter = counter + 1;
sprintf(text,"Counter = %-5d", counter);
lcd_gotoxy(0,1);
lcd_puts(text);
}

interrupt [EXT_INT1] void ext_int1_isr(void){
counter = counter - 1;
sprintf(text,"Counter = %-5d", counter);
lcd_gotoxy(0,1);
lcd_puts(text);
}

interrupt [TIM1_COMPA] void timer1_compa_isr(void){

}

void main(void){

DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (1<<DDB0);
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

DDRC=(1<<DDC7) | (1<<DDC6) | (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (1<<PORTD1) | (1<<PORTD0);

TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<COM1C1) | (0<<COM1C0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (1<<WGM12) | (1<<CS12) | (0<<CS11) | (0<<CS10);

TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x98;
OCR1AL=0x96;
OCR1BH=0x00;
OCR1BL=0x00;
OCR1CH=0x00;
OCR1CL=0x00;

TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (1<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);

EICRA=(0<<ISC31) | (0<<ISC30) | (0<<ISC21) | (0<<ISC20) | (1<<ISC11) | (0<<ISC10) | (1<<ISC01) | (0<<ISC00);
EICRB=(0<<ISC71) | (0<<ISC70) | (0<<ISC61) | (0<<ISC60) | (0<<ISC51) | (0<<ISC50) | (0<<ISC41) | (0<<ISC40);
EIMSK=(0<<INT7) | (0<<INT6) | (0<<INT5) | (0<<INT4) | (0<<INT3) | (0<<INT2) | (1<<INT1) | (1<<INT0);
EIFR=(0<<INTF7) | (0<<INTF6) | (0<<INTF5) | (0<<INTF4) | (0<<INTF3) | (0<<INTF2) | (1<<INTF1) | (1<<INTF0);

lcd_init(16);

#asm("sei")
sprintf(text,"Counter = %-5d", counter);
lcd_gotoxy(0,1);
lcd_puts(text);                      //puts pasti ada variablenya, dimana s = string
                                     //putsf = string flash ROM. gak perlu variable 

while (1){
      for (i=0; i<=15; i++){
        lcd_gotoxy(i,0);
        lcd_putchar(textfis[i]);
        delay_ms(200);
        }
      for (i=15; i>=1; i--){ 
        lcd_gotoxy(i,0);
       lcd_putchar(20);            //ditimpa dengan blank space = 20 (ASCII)
        delay_ms(200);
        }
      if (counter >10){
        PORTB.0 = 1;
        }
      else{
        PORTB.0 = 0;
        }
    } 
}



