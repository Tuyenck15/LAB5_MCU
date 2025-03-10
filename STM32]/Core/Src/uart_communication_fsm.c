/*
 * uart_communiation_fsm.c
 *
 *  Created on: Dec 9, 2024
 *      Author: Admin
 */

#include "uart_communication_fsm.h"

void uart_communiation_fsm(ADC_HandleTypeDef hadc1, UART_HandleTypeDef huart2) {
	switch(status_uart) {

	case WAIT_RST:
		if (command_flag == 1) {
			command_flag = 0;
			if (command[0] == 'R' && command[1] == 'S' && command[2] == 'T' && command[3] == '\0') {
				HAL_ADC_Start(&hadc1);
				ADC_value = HAL_ADC_GetValue(&hadc1);
				HAL_ADC_Stop(&hadc1);
				HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "\r\n"), 1000);
				status_uart = SEND_ADC;
				setTimer(1, 3000);
			}
		}
		break;

	case SEND_ADC:
		HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!ADC=%lu#\r\n", ADC_value), 1000);
		status_uart = WAIT_OK;
		break;

	case WAIT_OK:
		if (command_flag == 1) {
			command_flag = 0;
			if (command[0] == 'O' && command[1] == 'K' && command[2] == '\0') {
				HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "\r\n"), 1000);
				status_uart = WAIT_RST;
				clearTimer(1);
			}
		}
		if(timer_flag[1] == 1) {
			status_uart = SEND_ADC;
			setTimer(1, 3000);
		}
		break;
	default:
		break;
	}
}
