/*
 * motor.h
 *
 * Author:	Anna Selstam & Malin Ramkull
 * Date:	2022-01-04
 *
 * This is the device driver for the motor.
 *
 *
 */


#ifndef MOTOR_H_
#define MOTOR_H_

void motor_init(void);
void motor_set_speed(uint8_t speed);

#endif /* MOTOR_H_ */