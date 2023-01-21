/*
 * delay.inc
 *
 * Created: 2021-12-02
 * Author : Malin Ramkull, Anna Selstam
 *
 */ 

;==============================================================================
; Delay of ca 1s 
;	IN:		RVAL		= R24
;==============================================================================
delay_1_s:
	LDI		RVAL, 250 
	RCALL	delay_ms
	LDI		RVAL, 250 
	RCALL	delay_ms
	LDI		RVAL, 250 
	RCALL	delay_ms
	LDI		RVAL, 250 
	RCALL	delay_ms
	LDI		RVAL, 250 
	RCALL	delay_ms
	LDI		RVAL, 250 
	RCALL	delay_ms
	RET

;==============================================================================
; DD (including RCALL)
;==============================================================================
delay_ay:   /* UPPGIFT: komplettera med ett antal NOP-instruktioner!!! */
	NOP
	NOP
	NOP
	NOP
	
	RET

;==============================================================================
; Delay of 1 µs (including RCALL)
;==============================================================================
delay_1_micros:   
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP			; vi la till 8st dvs totalt 16

	RET

;==============================================================================
; Delay of 1 µs // 16-4 = 12 cyklar i hela rutinen under 
; Felmarginal har stor påverkan vid upphov till en liten fördröjning 
;	LDI + RCALL = 4 cycles
;==============================================================================
delay_micros:   
	RCALL	delay_ay
	DEC		R24
	CPI		R24, 0			
	BRNE	delay_micros	
	RET

;==============================================================================
; Delay of 1 ms
; Felmarginal kan försummas vid upphov till stor fördröjning
;	LDI + RCALL = 4 cycles
;==============================================================================
delay_ms:
	MOV		R19, R24
loop_dms:
	LDI		R24, 250
	RCALL	delay_micros
	LDI		R24, 250
	RCALL	delay_micros
	LDI		R24, 250
	RCALL	delay_micros
	LDI		R24, 250
	RCALL	delay_micros
	DEC		R19
	CPI		R19, 0			
	BRNE	loop_dms		
	RET
