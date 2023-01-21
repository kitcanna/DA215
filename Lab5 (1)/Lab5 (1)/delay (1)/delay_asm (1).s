/*
 * delay.inc
 *
 * Author:	Malin Ramkull & Anna Selstam
 * Date:	2021-11-25
 *
 * En subrutin med olika långa fördröjningar.  
 * Samtliga rutiner använder R24.
 */ 

.global delay_1_micros
.global delay_micros
.global delay_ms
.global delay_s


;==============================================================================
; delay of ca 1s (including RCALL)
;==============================================================================
delay_s:
	LDI		R24, 250 
	RCALL	delay_ms
	LDI		R24, 250 
	RCALL	delay_ms
	LDI		R24, 250 
	RCALL	delay_ms
	LDI		R24, 250 
	RCALL	delay_ms
	LDI		R24, 250 
	RCALL	delay_ms
	LDI		R24, 250 
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
delay_1_micros:   /* UPPGIFT: komplettera med ett antal NOP-instruktioner!!! */
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
delay_micros:   /* UPPGIFT: komplettera med ett antal NOP-instruktioner!!! */
	RCALL delay_ay
	DEC R24
	CPI R24, 0			; more loops to do?
	BRNE delay_micros	;	continue!
	RET

;==============================================================================
; Delay of 1 ms
; Felmarginal kan försummas vid upphov till stor fördröjning
;	LDI + RCALL = 4 cycles
;==============================================================================
delay_ms:
	MOV R19, R24
loop_dms:
	LDI R24, 250
	RCALL delay_micros
	LDI R24, 250
	RCALL delay_micros
	LDI R24, 250
	RCALL delay_micros
	LDI R24, 250
	RCALL delay_micros
	DEC R19
	CPI R19, 0			; more loops to do?
	BRNE loop_dms		;	continue!
	RET

