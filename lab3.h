/*
 * lab3.h
 *
 *  Created on: Sep 26, 2017
 *      Author: Derek
 */

#ifndef LAB3_H_
#define LAB3_H_

#define QUESTION_11

#include <stdint.h>

#ifdef QUESTION_9
static void itoa(uint32_t num, char * str, uint8_t base);
//Found at http://www.geeksforgeeks.org/convert-floating-point-number-string/ All credit given to those cool guys.
static void ftoa(float num, char * str, uint8_t afterpoint);
//ftoa helpers
static void reverse(char *str, int len);
uint8_t intToStr(uint32_t x, char str[], uint8_t d);
static void test_itoas(void);

#endif

#ifdef QUESTION_11
void characterizeChar(uint8_t data);
#endif

#endif /* LAB3_H_ */
