#include <mega128.h>
#include <alcd.h>
#include <stdio.h>
#define clock_freq 10000000.0                                //clock pas wizard punyanya ATMega128

unsigned int start_time, end_time, ov_counter;               //untuk menampung ICR1 awal
char text[16];
unsigned long int pulsa;
float periode;
bit flag = 0;                                                //0 itu start_time. 1 itu end_time

interrupt [EXT_INT0] void ext_int0_isr(void){

}

interrupt [TIM1_OVF] void timer1_ovf_isr(void){
ov_counter++;                                               //akan bertambah jika timer terjadi satu siklus (65ribu)
}

interrupt [TIM1_CAPT] void timer1_capt_isr(void){
if (flag == 0){
    start_time = ICR1H*256 + ICR1L;
    flag = 1;
    }
else{
    end_time = ICR1H*256 + ICR1L;
    pulsa = (unsigned long)ov_counter*65536 + ((unsigned long)end_time - (unsigned long)start_time);
    periode = (float)pulsa/clock_freq;    
    sprintf(text,"f = %6.2f Hz",1/periode);
    lcd_gotoxy(0,1);
    lcd_puts(text);
    ov_counter = 0;
    flag = 0;
    };
}

void main(void){
DDRC=(1<<DDC7) | (1<<DDC6) | (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
PORTD=(1<<PORTD7) | (1<<PORTD6) | (1<<PORTD5) | (1<<PORTD4) | (1<<PORTD3) | (1<<PORTD2) | (1<<PORTD1) | (1<<PORTD0);

TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<COM1C1) | (0<<COM1C0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(1<<ICNC1) | (1<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (1<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;
OCR1CH=0x00;
OCR1CL=0x00;

TIMSK=(0<<OCIE2) | (0<<TOIE2) | (1<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (1<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);

EICRA=(0<<ISC31) | (0<<ISC30) | (0<<ISC21) | (0<<ISC20) | (0<<ISC11) | (0<<ISC10) | (1<<ISC01) | (0<<ISC00);
EICRB=(0<<ISC71) | (0<<ISC70) | (0<<ISC61) | (0<<ISC60) | (0<<ISC51) | (0<<ISC50) | (0<<ISC41) | (0<<ISC40);
EIMSK=(0<<INT7) | (0<<INT6) | (0<<INT5) | (0<<INT4) | (0<<INT3) | (0<<INT2) | (0<<INT1) | (1<<INT0);
EIFR=(0<<INTF7) | (0<<INTF6) | (0<<INTF5) | (0<<INTF4) | (0<<INTF3) | (0<<INTF2) | (0<<INTF1) | (1<<INTF0);

lcd_init(16);
#asm("sei")
lcd_putsf("TES ICP...");

while (1){
     
      }
}