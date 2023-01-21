/*
 * regulator.h
 *
 * This is the device driver for the potentiometer.
 *
 * Editor:	Malin Ramkull & Anna Selstam
 * Date:	2022-01-04
 *
 */ 

#ifndef REGULATOR_H_
#define REGULATOR_H_

#include <inttypes.h>

enum state
{
	MOTOR_OFF,
	MOTOR_ON,
	MOTOR_RUNNING
}; 
typedef enum state state_t;

void regulator_init(void);
uint8_t regulator_read_value(void);

#endif /* REGULATOR_H_ */