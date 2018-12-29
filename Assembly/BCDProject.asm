			.INCLUDE <m128def.inc>
			.DEF bindata = R20
			.DEF bcddata = R21
			.DEF tenth = R22
			.DEF segdata = R0
			.ORG 0x0000
			RJMP main

			.ORG 0x0046
main:		LDI R16, HIGH(RAMEND)	;stack memory high
			OUT SPH, R16			;simpan sementara di R16
			LDI R16, LOW(RAMEND)	;stack memory low
			OUT SPL, R16			;simpan sementara di R16

			LDI R16, 0x00
			OUT DDRB, R16			;DDRB MENJADI INPUT
			LDI R16, 0xFF			;AKTIF PULL UP
			OUT PORTB, R16
			OUT DDRE, R16
			OUT DDRC, R16

loop:		IN bindata, PINB		;DATA DARI PIN B MASUK KE BINDATA
			RCALL bin2bcd			;JALANKAN SUB PROGRAM BINER TO BCD
			RCALL display			;JALANKAN SUB PROGRAM display
			RJMP loop

bin2bcd:	LDI tenth, 0			;PULUHANNYA = 0	

ulang:		CPI bindata, 10			;BANDINGKAN DENGAN 10 (DESIMAL)
			BRMI selesai			;BRANCH KE SELESAI KALAU NEGATIF
			INC tenth				;INCREMENT (TAMBAH SATU) PULUHUAN
			SUBI bindata, 10		;BINDATA = BINDATA - 10
			BRSH ulang	

selesai:	SWAP tenth				;tuker 4 bit depan dengan belakang
			OR tenth, bindata		;tenth + bindata (30 + 09 cnth)
			MOV bcddata, tenth
			RET

display:	PUSH bcddata			;simpan ke stack
			ANDI bcddata, 0x0F		;masking technique
			RCALL bcd27seg			;jalankan sub program
			OUT PORTE, segdata		;TAMPILKAN R0 KE PORT E
			POP bcddata				;AMBIL DATA ASLI DARI STACK
			SWAP bcddata
			ANDI bcddata, 0x0F		;TUTUPI 4 BIT DATA TERTINGGI
			RCALL bcd27seg			
			OUT PORTC, segdata
			RET

bcd27seg:	LDI ZH, high(TABLE<<1)	;AMBIL ALAMAT TERTINGGI DARI TABLE
			LDI ZL, low(TABLE<<1)	;AMBIL ALAMAT TERENDAH DARI TABLE
			ADD ZL, bcddata			;TABEL= TABEL +R16
			LPM						;AMBIL ISI (DARI Z DIMASUKKAN KE BCDDATA
			RET

TABLE: .DB 0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
