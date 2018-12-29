		.include <m128def.inc>
		.ORG 0x0000
		RJMP main	  	;relatif jump. lompat ke main

					  	;BACA DATA SHEET UNTUK SYNTAX

		.ORG 0x0046   	;karena slot di atmega128 yang kosong ada di slot 46
main: 	LDI R16, 0x00 	;langsung isi di 0x00 dengan register
		OUT DDRB, R16 	;dari R16 switch, dimasukkan ke port B pada chip
		LDI R16, 0xFF 	;0xFF  di hexa itu 1111
		OUT PORTB, R16	;akifkan pull up
		OUT DDRE, R16	;port E sebagai output

loop:	IN R17, PINB	;dari Pin B masuk ke R17
		COM R17			;isi di R17 dibalik
		OUT PORTE, R17	;data dari R17 dikirim ke port E
		RJMP loop		;loncat ke loop 
