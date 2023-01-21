/*
 * L3.asm
 *
 * Created: 2021-12-02
 * Author : Malin Ramkull, Anna Selstam
 *
 */ 

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
	.DEF MENU_CH	= R19

;==============================================================================
; Start of program
;==============================================================================
	.CSEG
	.ORG RESET

	RJMP init

	.ORG PM_START

	.INCLUDE "delay.inc"
	.INCLUDE "lcd.inc"
	.INCLUDE "keyboard.inc"
	.INCLUDE "Tarning.inc"
	.INCLUDE "stats.inc"
	.INCLUDE "statsdata.inc"
	.INCLUDE "monitor.inc"

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
menu:
	RCALL	lcd_init
	WRITESTRING Str_1

check:
	RCALL	read_keyboard
	LDI		MENU_CH, 0
	CP		RVAL, MENU_CH	;S1		//compare the pressed button (RVAL) with the stored digit (MENU_CH)
	BREQ	val1					//if equal, jump to val1

	LDI		MENU_CH, 4		;S2		
	CP		RVAL, MENU_CH
	BREQ	val2

	LDI		MENU_CH, 8		;S3
	CP		RVAL, MENU_CH
	BREQ	val3

	LDI		MENU_CH, 1		;S3
	CP		RVAL, MENU_CH
	BREQ	val4

	RJMP	check
	;RJMP	main			

;==============================================================================
; Subroutines for when a choice in the menu is pressed
;==============================================================================

val1: 

	RCALL	lcd_clear_display		//clears display
	WRITESTRING Str_3				//sets correct heading by subroutine in lcd.inc
	LDI		RVAL, 0b0011000000		//move cursor
	RCALL	LCD_WRITE_INSTR			

	RCALL	rolling					
	MOV		RVAL, R16				//since other code uses RVAL, we move the returned value from R16 to RVAL
	RCALL	store_stat				

	RCALL	our_to_ASCII			//uses our old converter to print the pressed KEY to the LCD
	RCALL	lcd_write_chr

	RCALL	delay_1_s				
	RJMP	menu

;==============================================================================
val2:
	//first part identical to val1 
	RCALL	lcd_clear_display
	WRITESTRING Str_4
	LDI		RVAL, 0b0011000000		
	RCALL	LCD_WRITE_INSTR

	RCALL	showstat

	RCALL	delay_1_s
	RJMP	menu

;==============================================================================
val3: 
	//first part identical to val1 
	RCALL	lcd_clear_display
	WRITESTRING Str_5
	LDI		RVAL, 0b0011000000		
	RCALL	LCD_WRITE_INSTR

	RCALL	clearstat

	RCALL	delay_1_s
	RJMP	menu

;==============================================================================
val4: 
	//first part identical to val1 
	RCALL	lcd_clear_display
	WRITESTRING Str_6
	LDI		RVAL, 0b0011000000		
	RCALL	LCD_WRITE_INSTR

	RCALL	monitor

	RCALL	delay_1_s
	RJMP	menu

;==============================================================================
; Other subroutines
;==============================================================================

//Convert to ASCII, return value in RVAL
our_to_ASCII:
	MOV		RVAL, R16		
	SUBI	RVAL, -0x30	
	RET




