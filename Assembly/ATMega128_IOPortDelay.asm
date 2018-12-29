		.include <m128def.inc>
		.ORG 0x0000
		RJMP main

		.ORG 0x0046
main:	LDI R16, 0x00
		OUT DDRB, R16

		LDI R16, 0xFF
		OUT PORTB, R16
		OUT DDRE, R16

loop:	SBI PORTE, 2 ;set bit in IO register PORT E,2
		CBI PORTE, 2 ;clear bit in IO register PORTE,2
		RJMP loop
