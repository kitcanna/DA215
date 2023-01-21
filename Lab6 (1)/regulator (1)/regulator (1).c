/*
 * regulator.c
 *
 * This is the device driver for the potentiometer.
 *
 * Editor:	Malin Ramkull & Anna Selstam
 * Date:	2022-01-04
 *
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "regulator.h"

/*	For storage of ADC value from temperature sensor.
	Initial value is good to use before A/D conversion is configured!	*/
static volatile uint16_t adc = 221;

/*
 * Interrupt Service Routine for the ADC.
 * The ISR will execute when a A/D conversion is complete.
 */
ISR(ADC_vect) 
{
	adc = ADCH;
}

void regulator_init(void) 
{
	// set reference voltage (internal 5V)
	ADMUX |= (1 << REFS0);											
	// select diff.amp 1x on  ADC1 ”Single Ended Input”
	ADMUX |= (1 << MUX0);	
	//	left adjustment of ADC value										
	ADMUX |= (1 << ADLAR);
	
	// prescaler 128
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);			
	// enable Auto Trigger
	ADCSRA |= (1 << ADATE);											
	// enable Interrupt
	ADCSRA |= (1 << ADIE);											
	// enable ADC
	ADCSRA |= (1 << ADEN);											

	// disable digital input on ADC0 and ADC1
	DIDR0 = 3;
	// disable USB controller (to make interrupts possible)
	USBCON = 0;
	// enable global interrupts
	sei();
	// start initial conversion
	ADCSRA |= (1 << ADSC);	

}

/*
 * Returns percent of power (0-100%).
 */
uint8_t regulator_read_value(void)
{
	return (adc*100)/255;
}
