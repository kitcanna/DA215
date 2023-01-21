/*
 * temp.h
 *
 * This is the device driver for the LM35 temperature sensor.
 *
 * Author:	Mathias Beckius
 * Date:	2014-12-07
 * Editor:	Malin Ramkull & Anna Selstam
 * Date:	2021-12-16
 *
 */ 

#ifndef TEMP_H_
#define TEMP_H_

#include <inttypes.h>

enum state
{
	SHOW_TEMP_C,
	SHOW_TEMP_F,
	SHOW_TEMP_CF
}; 
typedef enum state state_t;

void temp_init(void);
uint8_t temp_read_celsius(void);
uint8_t temp_read_fahrenheit(void);

#endif /* TEMP_H_ */