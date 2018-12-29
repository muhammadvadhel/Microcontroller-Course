#include <mega128.h>
#include <i2c.h>
#include <ds1307.h>
#include <alcd.h>
#include <stdio.h>
#include <delay.h>
#include <string.h>

unsigned char date[6], time[6], i, digit, key;
unsigned char tanggal, bulan, tahun, hari, jam, menit, detik;
char text[16];
char *nama_hari[7]={"Ahad","Senin","Selasa","Rabu","Kamis","Jumat","Sabtu"};

unsigned char read_keypad(void){
    unsigned char key_index;
    PORTB=0xFF;
    PORTB.4=0;
    key_index= (~PINB) & 0x0F;
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
    
    PORTB.4=1; PORTB.5=0;
    key_index= (~PINB) & 0x0F;
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
    
    PORTB.5=1; PORTB.6=0;
    key_index= (~PINB) & 0x0F;
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

    PORTB.6=1; PORTB.7=0;
    key_index= (~PINB) & 0x0F;
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

void input_tanggal(void){
lcd_clear();
lcd_putsf("Tgl (DD/MM/YY):");
lcd_gotoxy(0,1);

for(i=0; i<=5; i++){
    do{
    digit=read_keypad();
    }
    
    while((digit==16)||(digit==10)||(digit==11));
    sprintf(text,"%d",digit);
    lcd_puts(text);
    date[i]=digit;
    delay_ms(300);
    if(i==1 || i==3) lcd_putsf("/");  
  };

tanggal=date[0]*10 + date[1];
bulan=date[2]*10 + date[3];
tahun=date[4]*10 + date[5];
}

void input_hari(void){
lcd_clear();
lcd_putsf("Hari ke (0-6):");
lcd_gotoxy(0,1);

    do{
    digit=read_keypad();
    }
    
    while(digit>6);
    sprintf(text,"%d",digit);
    lcd_puts(text);
    hari=digit;
    delay_ms(300);
}

void input_jam(void){
lcd_clear();
lcd_putsf("Jam (HH:MM:SS):");
lcd_gotoxy(0,1);

for(i=0; i<=5; i++){
    do{
    digit=read_keypad();
    }
    
    while((digit==16)||(digit==10)||(digit==11));
    sprintf(text,"%d",digit);
    lcd_puts(text);
    time[i]=digit;
    delay_ms(300);
    if(i==1 || i==3) lcd_putsf(":");  
  };

jam=time[0]*10 + time[1];
menit=time[2]*10 + time[3];
detik=time[4]*10 + time[5];
}

void main(void){
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (1<<DDA1) | (0<<DDA0);
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (1<<PORTA0);

DDRB=(1<<DDB7) | (1<<DDB6) | (1<<DDB5) | (1<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (1<<PORTB3) | (1<<PORTB2) | (1<<PORTB1) | (1<<PORTB0);

DDRC=(1<<DDC7) | (1<<DDC6) | (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Bit-Banged I2C Bus initialization// I2C Port: PORTA // I2C SDA bit: 0 // I2C SCL bit: 1
// Bit Rate: 100 kHz // Note: I2C settings are specified in the // Project|Configure|C Compiler|Libraries|I2C menu.
i2c_init();

// DS1307 Real Time Clock initialization // Square wave output on pin SQW/OUT: On // Square wave frequency: 1Hz
rtc_init(0,1,0);

lcd_init(16);

input_tanggal();
input_hari();
input_jam();
rtc_set_date(hari,tanggal,bulan,tahun);
rtc_set_time(jam,menit,detik);

while (1)
      {
      rtc_get_date(&hari,&tanggal,&bulan,&tahun);
      lcd_clear();
      sprintf(text,"%02d/%02d/%4d %s",tanggal,bulan,2000+tahun,nama_hari[hari]);
      lcd_puts(text);
        
      rtc_get_time(&jam,&menit,&detik);
      sprintf(text,"%02d:%02d:%02d",jam,menit,detik);
      lcd_gotoxy(0,1);
      lcd_puts(text);
      delay_ms(500);
      }
}
