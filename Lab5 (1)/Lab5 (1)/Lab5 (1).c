/*
 *
 *
 * Author:	Anna Selstam & Malin Ramkull
 * Date:	2021-12-16
 *
 * Code loops the user always checking for the current_state,
 * and depending on the current_state it reads the pressed key (or no key)  
 * and follows instructions accordingly.
 *
 *
 */

#include <avr/io.h>
#include <stdio.h>
#include "hmi/hmi.h"
#include "temp/temp.h"
#include "numkey/numkey.h"
#include "delay/delay.h"

int main(void)
{	
	temp_init();
	hmi_init();
	numkey_init();
	
	int key;
	state_t current_state = SHOW_TEMP_C;
	state_t next_state = SHOW_TEMP_C;
	char temp_str[17];					//ska ha plats för 16 synliga tecken

	while (1) {
		key = numkey_read();
		switch (current_state) {
			
			case SHOW_TEMP_C:
					if ((key == '1')||(key == NO_KEY)){
						sprintf(temp_str, "%u%cC", temp_read_celsius(), 0xDF);
						output_msg("TEMPERATURE:", temp_str, 0);
					}
					else if (key == '2'){
						next_state = SHOW_TEMP_F;
					}
					else if (key == '3'){
						next_state = SHOW_TEMP_CF;
					} break;
					
			case SHOW_TEMP_F: 
					if ((key == '2') || (key == NO_KEY)){
						sprintf(temp_str, "%u%cF", temp_read_fahrenheit(), 0xDF);
						output_msg("TEMPERATURE:", temp_str, 0);
					}
					else if (key == '1'){
						next_state = SHOW_TEMP_C;
					}
					else if (key == '3'){
						next_state = SHOW_TEMP_CF;
					} break;
					
			case SHOW_TEMP_CF:
					 if ((key == '3') || (key == NO_KEY)){
						 sprintf(temp_str, "%u%cC %u%cF", temp_read_celsius(), 0xDF, temp_read_fahrenheit(), 0xDF);
						 output_msg("TEMPERATURE:", temp_str, 0);
					 }
					else if (key == '1'){
						next_state = SHOW_TEMP_C;
					}
					else if (key == '2'){
						next_state = SHOW_TEMP_F;
					} break;
					
		}
		current_state = next_state;
	}
}