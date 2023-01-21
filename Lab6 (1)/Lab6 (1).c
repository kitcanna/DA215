/*
 *
 *
 * Author:	Anna Selstam & Malin Ramkull
 * Date:	2022-01-04
 *
 * Program that runs a small motor/fan, 
 * displaying the current state and the power (percent).
 *
 */

#include <avr/io.h>
#include <stdio.h>
#include "hmi/hmi.h"
#include "common.h"
#include "regulator/regulator.h"
#include "numkey/numkey.h"
#include "delay/delay.h"
#include "motor/motor.h"

int main(void)
{	
	regulator_init();
	hmi_init();
	numkey_init();
	motor_init();
	
	uint8_t key;
	state_t current_state = MOTOR_OFF;
	state_t next_state = MOTOR_OFF;
	char state_str[17];
	char regulator_str[17];					//ska ha plats för 16 synliga tecken

    while(1) {
	    key = numkey_read();
	    switch(current_state){
		    case MOTOR_ON:
				if (regulator_read_value() > 0) {
					next_state = MOTOR_RUNNING;
				}
				else if (key == '1'){
					next_state = MOTOR_OFF;
				}
				sprintf(state_str, "MOTOR ON");
				break;
		   
		    case MOTOR_OFF:
				if(key == '2' && regulator_read_value() == '0') {
					next_state = MOTOR_ON;
					motor_set_speed(0);
				} 
				sprintf(state_str, "MOTOR OFF");
				break;

		    case MOTOR_RUNNING:
				motor_set_speed(regulator_read_value());
				if (key == '1') {
					next_state = MOTOR_OFF;
				}
				sprintf(state_str, "MOTOR RUNNING");
				break;
	    }
	    sprintf(regulator_str,"%u%c",regulator_read_value(), '%');
	    output_msg(state_str, regulator_str, 0);
	    current_state = next_state;
    }
    
}