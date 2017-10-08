/*
 * HSMCLK_config.c
 *
 *  Created on: Sep 25, 2017
 *      Author: Derek Wright
 */
#ifdef HOMEWORK
void HSMCLK_config(void) {

    uint32_t sels = CS->CTL1 & CS_CTL1_SELS_MASK; // can be inspected to confirm clock setting. default to DCO

    CS->KEY = 0x0000695A; // CS password

    //CS->CTL1 = CS_CTL1_SELS__HFXTCLK; // change clock source if you want

    CS->CTL0 |= CS_CTL0_DCOEN;
    CS->CLKEN |= CS_CLKEN_HSMCLK_EN; // enable HSMCLK
    CS->KEY = 0; // relock

    P4->SEL0 |= BIT4; // primary mode
    P4->SEL1 &= ~BIT4;
    P4->DIR |= BIT4; //output

}
#endif
