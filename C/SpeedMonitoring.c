#include <mega128.h>
#include <alcd.h>
#include <stdio.h>
#define distance 10.0
#define clock_freq 10000000.0

unsigned long int iterasi, pulsa;
float time, speed;
char text[16];

interrupt [EXT_INT0] void ext_int0_isr(void){
TCNT1H = 0x00; TCNT1L =0x00;
iterasi = 0;
TCCR1B = 0x09;
lcd_gotoxy(0,1);
lcd_putsf("Start...        ");
lcd_gotoxy(0,0);
lcd_putsf("Speed Monitoring");
EIMSK = 0x02;           //enable INT1 tapi disable INT0
}

interrupt [EXT_INT1] void ext_int1_isr(void){
TCCR1B = 0x00;
pulsa = iterasi*50000 + (unsigned long)TCNT1H*256 + (unsigned long)TCNT1L;
time = (float)pulsa/clock_freq;
speed = distance/time;
lcd_clear();

sprintf(text,"t = %7.3f s",time);
lcd_gotoxy(0,0);
lcd_puts(text);

sprintf(text,"v = %7.3f m/s",speed);
lcd_gotoxy(0,1);
lcd_puts(text);
                          //start timer1
EIMSK = 0x01;             //enable dua duanya
}

interrupt [TIM1_COMPA] void timer1_compa_isr(void){
iterasi++;
}

void main(void){
DDRC=(1<<DDC7) | (1<<DDC6) | (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (1<<PORTD1) | (1<<PORTD0);

TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<COM1C1) | (0<<COM1C0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (1<<WGM12) | (0<<CS12) | (0<<CS11) | (1<<CS10);
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0xC3;
OCR1AL=0x4F;
OCR1BH=0x00;
OCR1BL=0x00;
OCR1CH=0x00;
OCR1CL=0x00;

TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (1<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);

EICRA=(0<<ISC31) | (0<<ISC30) | (0<<ISC21) | (0<<ISC20) | (1<<ISC11) | (0<<ISC10) | (1<<ISC01) | (0<<ISC00);
EICRB=(0<<ISC71) | (0<<ISC70) | (0<<ISC61) | (0<<ISC60) | (0<<ISC51) | (0<<ISC50) | (0<<ISC41) | (0<<ISC40);
//EIMSK=(0<<INT7) | (0<<INT6) | (0<<INT5) | (0<<INT4) | (0<<INT3) | (0<<INT2) | (1<<INT1) | (1<<INT0);
EIFR=(0<<INTF7) | (0<<INTF6) | (0<<INTF5) | (0<<INTF4) | (0<<INTF3) | (0<<INTF2) | (1<<INTF1) | (1<<INTF0);
EIMSK=0x01;     //enable INT0 tapi disable INT1

lcd_init(16);
lcd_putsf("Speed Monitoring");

#asm("sei")

while (1){

      }
}
