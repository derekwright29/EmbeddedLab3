#include "msp.h"
#include <stdint.h>
#include <stdlib.h>

#include "lab3.h"
#include "uart.h"
#include "circBuff.h"
//#include "\Documents\ECEN2440_Lab2\port.h"

/**
 * main.c
 */
#ifdef QUESTION_11
circBuff init;
circBuff * Rx_data = &init;
volatile CB_STATUS status;
volatile uint8_t input;
volatile uint8_t isEnterChar = 0;
volatile uint8_t alphas;
volatile uint8_t whitespaces;
volatile uint8_t puncs;
volatile uint8_t nums;
#endif

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    #if defined(QUESTION_5) || defined(QUESTION_7) || defined(QUESTION_10) || defined(QUESTION_11)
    //config LED TODO Make LED config function
    P1->SEL0 &= ~BIT0; //SET TO GPIO
    P1->SEL0 &= ~BIT0;
    P1->DIR |= BIT0; // SET AS OUTPUT
    P1->OUT |= BIT0; //P1.0 output low

    UART_port_config();
    #if defined(QUESTION_5) || defined(QUESTION_7)
    test_UART();
    #endif
    #endif

    #ifdef QUESTION_8
    testBuffer();
    #endif

    #ifdef QUESTION_9
    test_itoas();
    #endif

    #ifdef QUESTION_11
    initCircBuff(&Rx_data, 256);
    #endif

    __enable_irq();

	while(1){
    #ifdef QUESTION_11
	    if (isEnterChar) {
	        while(!isBufEmpty(Rx_data)) {
	            input = removeBuf(Rx_data);
	            characterizeChar(input);
	            UART_putChar(input);
	        }
	        Rx_data->head = Rx_data->base; //reset buff
	        Rx_data->tail = Rx_data->base;
	   }
    #endif
	}
}
