/*
 * delay.inc
 *
 * Author:	Malin Ramkull & Anna Selstam
 *
 * Date:	2021-11-25
 */ 

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
; Delay of 1 ?s (including RCALL)
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
; Delay of 1 ?s // 16-4 = 12 cyklar i hela rutinen under 
; Felmarginal har stor p?verkan vid upphov till en liten f?rdr?jning 
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
; Felmarginal kan f?rsummas vid upphov till stor f?rdr?jning
;	LDI + RCALL = 4 cycles
;==============================================================================
delay_ms:
	MOV R18, R24
loop_dms:
	LDI R24, 250
	RCALL delay_micros
	LDI R24, 250
	RCALL delay_micros
	LDI R24, 250
	RCALL delay_micros
	LDI R24, 250
	RCALL delay_micros
	DEC R18
	CPI R18, 0			; more loops to do?
	BRNE loop_dms		;	continue!
	RET