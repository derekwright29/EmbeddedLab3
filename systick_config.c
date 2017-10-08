/*
 * systick_config.c
 *
 *  Created on: Sep 26, 2017
 *      Author: admin
 */

#ifdef SYSTICK

void config_SysTick() {

//LED config
    P1->SEL0 &= ~BIT0;              //P1.0 to General I/O Mode (Need 0,0 in SEL0 and 1 registers, 0th bit
    P1->SEL1 &= ~BIT0;

    P1->DIR |= BIT0;                  //P1.0 set to output direction (Need a 1 in the 0th bit position of register

    P1->OUT &= ~BIT0;               //P1.0 output low

    //SysTick config
    SysTick->CTRL |= (BIT2 | BIT0); // enable, clock
    SysTick->LOAD = SysTick_LOAD_RELOAD_Msk; // set systick to max value
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;

    NVIC_EnableIRQ(SysTick_IRQn);


}


void SysTick_Handler() {
    P1->OUT ^= BIT0;
    while(1);
}
#endif
