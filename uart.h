/*
 * uart.h
 *
 *  Created on: Sep 26, 2017
 *      Author: jasc5797
 */

#ifndef UART_H_
#define UART_H_
#include <stdint.h>

#define QUESTION_11

typedef enum BAUD_t {
    BAUD9600,
//    BAUD57600,
//    BAUD115200, TODO: config these bauds

}BAUD;

void test_UART(void);
void config_baud(BAUD baud);

void UART_port_config();
void EUSCIA0_IRQHandler();
void UART_send_byte(uint8_t data);
void UART_send_n(uint8_t * data, uint32_t length);

void UART_putChar(uint8_t tx_data);
void UART_putChar_n(uint8_t * tx_data, uint32_t length);

#endif /* UART_H_ */
