/*
 * uart.c
 *
 *  Created on: Sep 26, 2017
 *      Author: jasc5797
 */
#include "msp.h"
#include "uart.h"
#include "circBuff.h"
#ifdef QUESTION_11
extern circBuff * Rx_data;
extern volatile CB_STATUS status;
extern volatile uint8_t isEnterChar;
#endif
void EUSCIA0_IRQHandler() {
    if (EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG); // if trasmit
    if(EUSCI_A0->IFG & EUSCI_A_IFG_RXIFG) {
    #ifdef QUESTION_11
        if(EUSCI_A0->RXBUF == 0x0D || status == CB_FULL){
            EUSCI_A0->IE &= ~EUSCI_A_IE_RXIE; // turn off receive interrupts
            isEnterChar = 1; // set flag to main
        }
        else
            status = addToBuf(Rx_data, EUSCI_A0->RXBUF);
    #endif
        //shiftbuff_to_circbuff();
        P1->OUT ^= BIT0; // test toggle LED
        #ifdef QUESTION_10
        EUSCI_A0->TXBUF = EUSCI_A0->RXBUF; //echo
        #endif
    }
    EUSCI_A0->IFG = 0;//reset
}

#if defined(QUESTION_2) || defined(QUESTION_10) || defined(QUESTION_11)

void UART_port_config() {
    //UART pin config
    P1->SEL1 &= ~(BIT2 | BIT3);
    P1->SEL0 |= BIT2 | BIT3;

    //UART config
    EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST;     //Put eUSCI in reset

    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_PEN;      //Parity Disable
    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_MODE_3;   //Set to UART mode (not with Automatic baud)
    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_MSB;      //Set to LSB first
    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SEVENBIT; //Set to 8-bit data
    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SPB;      //One stop bit
    EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SSEL__SMCLK; // select clock for easy baud rate selection
    config_baud(BAUD9600);

    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;    //Initialize eUSCI
    //interrupt enable
    EUSCI_A0->IE |= EUSCI_A_IE_RXIE; //receive interrupt. Buffer full -- needs to be read
    EUSCI_A0->IE |= EUSCI_A_IE_TXIE; //transmit buffer empty, ready to go.


    NVIC_EnableIRQ(EUSCIA0_IRQn);
}
#endif

void config_baud(BAUD baud){
    if (baud == BAUD9600) {
        EUSCI_A0->BRW = 19; // from 3MHz / 9600 / 16
        EUSCI_A0->MCTLW |= EUSCI_A_MCTLW_OS16; // oversample set
        EUSCI_A0->MCTLW |= (0xAA << EUSCI_A_MCTLW_BRS_OFS); // BRSx
        EUSCI_A0->MCTLW |= (8 << EUSCI_A_MCTLW_BRF_OFS); //BRFx
    }

}

void UART_putChar(uint8_t tx_data) {
    while(EUSCI_A0->STATW & EUSCI_A_STATW_BUSY);
    EUSCI_A0->TXBUF = tx_data;
}
void UART_putChar_n(uint8_t * tx_data, uint32_t length){
    uint32_t i;
    for(i = 0; i < length; i++) {
        UART_putChar(tx_data[i]);
    }
}

void test_UART() {
    while(1) {
    #ifdef QUESTION_7
        UART_putChar_n("Why not Zoidberg?", 17);
    #endif
    #ifdef QUESTION_5
        UART_putChar(0xAA);
    #endif
    }
}
