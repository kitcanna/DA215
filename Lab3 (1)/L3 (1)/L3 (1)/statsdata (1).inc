/*
 * statsdata.inc
 *
 * Created: 2021-12-07
 * Author : Malin Ramkull, Anna Selstam
 *
 * Space in the RAM to save the results from dice throws.
 *
 * The following functions are provided:
 *	store_stat (R24 contains the dice value)
 *			The function will increment the total number of throws and the
 *			number of throws with results equals R24.
 *	get_stat (R24 gives the value for which the result is retrieved.)
 *			If R24 = 0, the total number of throws shall be returned.
 * 			The result is returned in R24.
 *	clear_stat (no parameters in nor out)
 *			Clears all data.
 */ 

;==============================================================================
; DEFINE BYTES AND ADDRESS
;==============================================================================
.DSEG						;Start in data-memory (RAM)
.ORG		0x100			;Starting-address of data segment to 0x100
save_byte:	.BYTE 7			;Reserves 7 bytes for storage
.CSEG						;Move to program-memory (ROM)

;==============================================================================
; STORE RVAL FROM READ KEYBOARD
;	IN:		RVAL		= R24
;
; Initiates the X-pointer, increments our total counter and 
; takes the rolled dice and uses it as a index pointer, and 
; increments the value at said index
;==============================================================================
store_stat: 
	LDI		XL, LOW(save_byte<<1)		
	LDI		XH, HIGH(save_byte<<1)

	PUSH	RVAL
	LD		RVAL, X
	INC		RVAL
	ST		X, RVAL
	POP		RVAL

	ADD		XL, RVAL
	LD		RVAL, X
	INC		RVAL
	ST		X, RVAL
	RET

;==============================================================================
; SUBROUTINE CALLED BY "stats.inc" 
;	IN:		RVAL		= R24
;
; Uses the rolled dice as the index to get the value 
; stored in that index
;==============================================================================
get_stat:
	LDI		XH, HIGH(save_byte<<1)
	LDI		XL, LOW(save_byte<<1)
	ADD		XL, RVAL
	LD		RVAL, X
	RET

;==============================================================================
; SUBROUTINE CALLED BY "stats.inc" 
;	IN:		RVAL		= R24
;
; Initiates the X-pointer and loops around all of our storage bytes
; until we get back to 0 (hard code....)
;==============================================================================
clear_stat:
	LDI		XH, HIGH(save_byte<<1)
	LDI		XL, LOW(save_byte<<1)

malle:					
	LDI		RVAL, 0 
	ST		X+,	RVAL
	CPI		XL, 8
	BRNE	malle

	RET
