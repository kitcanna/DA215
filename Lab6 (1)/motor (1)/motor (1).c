/*
 * motor.c
 *
 * Author:	Anna Selstam & Malin Ramkull
 * Date:	2022-01-04
 *
 * This is the device driver for the motor.
 *
 *
 */ 
#include <avr/io.h>

void motor_init(void) {
	// set PC6 (digital pin 5) as output
	DDRC |= (1<<6);
	
	// Set OC3A (PC6) to be cleared on Compare Match (Channel A)
	TCCR3A |= (1<<COM3A1) | (0<<COM3A0);

	// Waveform Generation Mode 5, Fast PWM (8-bit)
	TCCR3A |= (1<<WGM30) | (0<<WGM31);
	TCCR3B |= (1<<WGM32) | (0<<WGM33);
	
	// Timer Clock, 16/64 MHz = 1/4 MHz (prescale)
	TCCR3B |= (1<<CS30 ) | (1<<CS31) | (0<<CS32);
}

/* 
 * OCR är ett 16 bitars register.
 * Därför måste vi ge ett värde inom 8 bit.
 */
void motor_set_speed(uint8_t speed) {
	// not used, always 0
	OCR3AH = 0;
	
	// set PWM value
	OCR3AL = (speed*255)/100;
}

