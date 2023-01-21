;
; Lab22.asm
;
; Created: 2021-11-25 09:56:21
; Author : Malin Ramkull & Anna Selstam
;


; Replace with your application code
;==============================================================================
; Definitions of registers, etc. ("constants")
;==============================================================================
	.EQU RESET		= 0x0000
	.EQU PM_START	= 0x0056
	.DEF TEMP		= R16
	.DEF RVAL		= R24
	.EQU NO_KEY		= 0x0F
	.DEF KEY		= R23
	.DEF LAST_KEY	= R25
	.DEF COUNT		= R22

;==============================================================================
; Start of program
;==============================================================================
	.CSEG

	.ORG PM_START
	.INCLUDE "lcd.inc"
	.INCLUDE "delay.inc"

	.ORG RESET

	RJMP init

;==============================================================================
; Basic initializations of stack pointer, I/O pins, etc.
;==============================================================================
init:
	; Set stack pointer to point at the end of RAM.
	LDI TEMP, LOW(RAMEND)
	OUT SPL, TEMP
	LDI TEMP, HIGH(RAMEND)
	OUT SPH, TEMP
	; Initialize pins
	CALL init_pins
	CALL lcd_init
	; Jump to main part of program
	RJMP main

;==============================================================================
; Initialize I/O pins
;==============================================================================
init_pins:	

	LDI TEMP, 0x0
	OUT DDRE, TEMP
	
	LDI TEMP, 0xFF
	OUT DDRD, TEMP
	OUT DDRC, TEMP
	OUT DDRB, TEMP
	OUT DDRF, TEMP

	RET

;==============================================================================
; Main part of program
;==============================================================================
main:	
	 
	LCD_WRITE_CHAR 'K'
	LCD_WRITE_CHAR 'A'
	LCD_WRITE_CHAR 'Y'
	LCD_WRITE_CHAR ':'
	
	/*LDI		RVAL, 0b0011000000 ; move cursor
	RCALL	LCD_WRITE_INSTR

	LDI		RVAL, 39
	RCALL	delay_micros*/

loop_clear_count: 
	LDI		COUNT, 0

loop: 
	CALL	read_keyboard
	MOV		KEY, RVAL
	MOV		LAST_KEY, RVAL
	CPI		KEY, NO_KEY
	BREQ	loop			;if input is NO_KEY jump to loop

	;Calc position for char
	LDI		R24, 0xC0
	ADD		R24, COUNT
	RCALL	lcd_write_instr 
	RCALL	delay_micros

	;Convert to ASCII and write to LCD
	SUBI	KEY, -48
	MOV		R24, KEY
	RCALL	lcd_write_chr
	RCALL	delay_micros

	;Increase counter but if >16 clear by calling loop_clear_count:
	INC		COUNT
	CPI		COUNT, 17
	BREQ	loop_clear_count
	RCALL	delay_ms

	;Check if key is released
loop_no_key:
	CALL	read_keyboard
	CP		LAST_KEY, RVAL 

forever:
	RJMP forever
	RJMP main	;2cycles


read_keyboard:
	LDI R18, 0	; reset counter


scan_key:
	MOV R19, R18
	LSL R19
	LSL R19
	LSL R19
	LSL R19
	OUT PORTB, R19		; set column and row
	NOP			; a minimum of 2 NOP's is necessary!
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	SBIC PINE, 6
	RJMP return_key_val
	INC R18
	CPI R18, 12
	BRNE scan_key
	LDI R18, NO_KEY		; no key was pressed!
return_key_val:
	MOV RVAL, R18
	RET
