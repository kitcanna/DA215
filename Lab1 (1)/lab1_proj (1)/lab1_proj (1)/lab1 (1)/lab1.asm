/*
 * lab1.asm
 * 
 * This is a very simple demo program made for the course DA215A at
 * Malmö University. The purpose of this program is:
 *	-	To test if a program can be transferred to the ATmega32U4
 *		microcontroller.
 *	-	To provide a base for further programming in "Laboration 1".
 *
 * After a successful transfer of the program, while the program is
 * running, the embedded LED on the Arduino board should be turned on.
 * The LED is connected to the D13 pin (PORTC, bit 7).
 *
 * Author:	Mathias Beckius
 *
 * Date:	2014-11-05
 */ 
 
;==============================================================================
; Definitions of registers, etc. ("constants")
;==============================================================================
	.EQU RESET		= 0x0000
	.EQU PM_START	= 0x0056
	.DEF TEMP		= R16
	.DEF RVAL		= R24
	.EQU NO_KEY		= 0x0F

;==============================================================================
; Start of program
;==============================================================================
	.CSEG
	.ORG RESET
	RJMP init

	.ORG PM_START
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
	; Jump to main part of program
	RJMP main

;==============================================================================
; Initialize I/O pins
;==============================================================================
init_pins:	
	LDI R16, 0x80
	OUT DDRC, TEMP

	LDI TEMP, 0xFF
	OUT DDRB, TEMP 
	OUT DDRF, TEMP

	/*LDI TEMP, 0xFF
	OUT PORTB, TEMP*/

	LDI TEMP, 0x00
	CBI PORTE,6

	RET

;==============================================================================
; Main part of program
;==============================================================================
main:		
	/*LDI TEMP, 0xFF
	OUT PORTF, TEMP*/

	IN TEMP, PINB
	COM TEMP
	MOV RVAL, TEMP

	CALL read_keyboard
	LSL RVAL
	LSL RVAL
	LSL RVAL
	LSL RVAL

	OUT PORTF, RVAL
	NOP 
	NOP 

	/*LDI TEMP, 0x10
	OUT PORTB, TEMP*/

	/*SBI PORTC, 7		; 2 cycles

	NOP					; 1 cycle x 6
	NOP
	NOP
	NOP
	NOP
	NOP
	CBI PORTC, 7		; 2 cycles
	NOP					; 1 cycle x 4
	NOP
	NOP
	NOP
*/
	RJMP main			; 2 cycles

read_keyboard:
	LDI R18, NO_KEY		; reset counter
scan_key:
	MOV R19, R18
	LSL R19
	LSL R19
	LSL R19
	LSL R19
	OUT PORTB, R19		; set column and row		//1 cycle on
	NOP			; a minimum of 2 NOP's is necessary! //1 cycle on
	NOP												//1 cycle on
	SBIC PINE, 6				//3 cycle max off	
	RJMP return_key_val			//2 cycles off
	INC R18
	CPI R18, 12
	BRNE scan_key
	LDI R18, NO_KEY		; no key was pressed!
return_key_val:
	MOV RVAL, R18
	RET