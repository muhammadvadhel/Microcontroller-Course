;MUHAMMAD VADHEL AKBARIZA, 1606885782

		.INCLUDE <m128def.inc>
		.ORG 0x00
		RJMP main

		.ORG 0x0046
main:	LDI R16, HIGH(RAMEND)	;stack memory high
		OUT SPH, R16			;simpan sementara di R16
		LDI R16, LOW(RAMEND)	;stack memory low
		OUT SPL, R16			;simpan sementara di R16

		LDI R16, 0x00			;mendefisikan DDRB sebagai input yang bernilai 0
		OUT DDRB, R16
		LDI R16, 0xFF
		OUT PORTB, R16
		OUT DDRE, R16			;mendefinisikan DDRE sebagai output

		LDI R19, 0B00000001		;data biner 8bit pada R19
turun:	PUSH R19				;simpan data asli
		COM R19					;reverse data menjadi 0B11111110
		OUT PORTE, R19			;data R19 dikirim ke Port E
		RCALL delay_05			;memanggil label delay_05
		CLC						;clear carry
		POP R19					;ambil lagi data asli dari stack
		ROL R19					;menggeser data R19 ke kiri
		BRCS rotate				;Branch if carry set
		RJMP turun				;looping ke label "loop"

rotate:	LDI R20, 0B01000000		;data register R20

naik :	PUSH R20				;menyelamatkan data
		COM R20					;data register di reverse
		OUT PORTE, R20			;data keluar ke port E
		RCALL delay_05
		CLC						;clear carry
		POP R20					;ambil data asli pada register
		ROR R20					;geser ke kanan
		BRCS rotate1			;Branch ke label rotate1
		RJMP naik

rotate1:LDI R21, 0B00000010		;data register R21

turun1 :PUSH R21				;menyelamatkan data
		COM R21					;data register di reverse
		OUT PORTE, R21			;data keluar ke port E
		RCALL delay_05
		CLC						;clear carry
		POP R21					;ambil data asli pada register
		ROL R21					;geser ke kiri
		BRCS rotate				;branch ke label rotate
		RJMP turun1

delay_05: 						;subroutine
		LDI R16, 8				;mengisi R16 dengan 8 

outer_loop:
		LDI R24, LOW(3037)		;mengisi R24 dan R25 dengan 3037
		LDI R25, HIGH(3037)

delay_loop:
		ADIW R24, 1				;add immediate to word
		BRNE delay_loop			;jika tidak sama dengan nol, akan kembali ke delay_loop
		DEC R16					;decrement pada R16
		BRNE outer_loop			;akan kembali ke outer_loop jika tidak sama dengan nol
		RET						;kembali ke subroutine
