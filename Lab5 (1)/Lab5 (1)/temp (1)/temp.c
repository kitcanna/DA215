/*
 * temp.c
 *
 * This is the device driver for the LM35 temperature sensor.
 *
 * Author:	Mathias Beckius
 * Date:	2014-12-07
 * Editor:	Malin Ramkull & Anna Selstam
 * Date:	2021-12-09
 *
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "temp.h"

/*	For storage of ADC value from temperature sensor.
	Initial value is good to use before A/D conversion is configured!	*/
static volatile uint16_t adc = 221;

/*
 * Interrupt Service Routine for the ADC.
 * The ISR will execute when a A/D conversion is complete.
 */
ISR(ADC_vect)
{
	unsigned char low, high;
	low = ADCL;					// read ADC value (low byte first!)
	high = ADCH;				// read ADC value high byte
	adc = (high<<8) + low;		// build (16 bit) value
}

/*
 * Initialize the ADC and ISR.
 */
void temp_init(void)
{
	//set reference voltage (internal 5V)
	ADMUX |= (1<<REFS0) | (0<<REFS1);
	
	//select diff.amp 10x on ADC0 & ADC1, right adjustment of ADC value
	ADMUX |= (1<<MUX3) | (1<<MUX0) | (0 << ADLAR);
	
	//prescaler 128
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1 << ADPS0);
	
	//enable Auto Trigger
	ADCSRA |= (1<<ADATE);

	//enable Interrupt
	ADCSRA |= (1<<ADIE);
	
	//enable ADC
	ADCSRA |= (1<<ADEN);
	
	//disable digital input on ADC0 and ADC1 (REDAN GJORT)
	DIDR0 = 3;
	
	//disable USB controller (to make interrupts possible) (REDAN GJORT)
	USBCON = 0;
	
	//enable global interrupts, start initial conversion
	sei();
	
	//UPPGIFT: gör så att den initiala // A/D-omvandlingen sker (detta är inte free running mode)
	ADCSRA |= (1<<ADSC);	

}

/*
 * Returns the temperature in Celsius.
 */
uint8_t temp_read_celsius(void)
{
	uint16_t adc_correction = adc * 98;
	uint16_t temp = adc_correction / 1000;
	// round up?
	if ((adc_correction % 1000) >= 500) {
		temp++;
	}
	return (uint8_t) temp;
}

/*
 * Returns the temperature in Fahrenheit.
 */
uint8_t temp_read_fahrenheit(void)
{
	uint16_t convert = ((temp_read_celsius() * 90) / 5) + 320;
	uint16_t temp = convert / 10;
	// round up?
	if ((convert % 10) >= 5) {
		temp++;
	}
	return (uint8_t) temp;
}