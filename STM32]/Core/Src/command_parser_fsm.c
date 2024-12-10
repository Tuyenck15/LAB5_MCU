/*
 * command_parser_fsm.c
 *
 *  Created on: Dec 9, 2024
 *      Author: Admin
 */

#include "command_parser_fsm.h"


void command_parser_fsm() {
	switch(status_parser) {
	case INIT_STR:
		if(temp == '!') {
			status_parser = WAIT_END;
			command_index = 0;
		}
		break;

	case WAIT_END:
		if(temp == '#') {
			status_parser = INIT_STR;
			command[command_index] = '\0';
			command_flag = 1;
		}
		else {
			if (temp == '!')
				command_index = 0;
			else {
				command[command_index++] = temp;
				if (command_index == MAX_BUFFER_SIZE) command_index = 0;
			}
		}
		break;
	default:
		break;
	}
}
