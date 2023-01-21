/*
 *	Tarning.inc
 *
 * Created: 2021-12-02
 * Author : Malin Ramkull, Anna Selstam
 *
 */ 

;==============================================================================
; CODE ROLLS A DICE AND RETURNS A "RANDOM" NUMBER
;	IN:		RVAL		= R24
;			NO_KEY		= 0x0F
;	OUT:	R16			= Contains rolled number 
;==============================================================================


rolling: 
	WRITESTRING Str_2

roll_dice:
	LDI		R16,6
test: 
	NOP
	NOP
	RCALL	read_keyboard
	CP		RVAL, MENU_CH
	BREQ	roll
	RET
roll:
	DEC		R16
	BREQ	roll_dice
	RJMP	test