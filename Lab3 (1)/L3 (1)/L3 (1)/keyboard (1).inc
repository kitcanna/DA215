/*
 * keyboard.inc
 *
 * Created: 2021-12-02
 * Author : Malin Ramkull, Anna Selstam
 *
 */ 

;==============================================================================
; CODE CHECKS WHAT KEY IS PRESSED AND RETURNS IT IN RVAL
;	IN:		RVAL		= R24
;			NO_KEY		= 0x0F
;	OUT:	RVAL		= Contains number 
;==============================================================================

read_keyboard:
	LDI		R18, 0						; reset counter

scan_key:
	MOV		R19, R18
	LSL		R19
	LSL		R19
	LSL		R19
	LSL		R19
	OUT		PORTB, R19					; set column and row
	LDI		RVAL, 10
	RCALL	delay_ms
	SBIC	PINE, 6
	RJMP	return_key_val
	INC		R18
	CPI		R18, 12
	BRNE	scan_key
	LDI		R18, NO_KEY					; no key was pressed!

return_key_val:
	MOV		RVAL, R18
	RET

;==============================================================================
; CONVERT TO ASCII
;==============================================================================

map_table: .DB "147*2580369#"			;define bytes	

to_ASCII:
	LDI		ZH, high(map_table<<1)		;initalize Z pointer
	LDI		ZL, low(map_table<<1)
	ADD		ZL, RVAL					;Add index
	LDI		RVAL, 0x00
	ADC		ZH, RVAL					;Add 0 to catch Carry, if present
	LPM		RVAL, Z
	RET

