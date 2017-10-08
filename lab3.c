/*
 * lab3.c
 *
 *  Created on: Sep 26, 2017
 *      Author: Derek, luke ;)
 */
#include "lab3.h"
#include <stdlib.h>
#include <math.h>

#ifdef QUESTION_11
extern volatile uint8_t alphas;
extern volatile uint8_t whitespaces;
extern volatile uint8_t puncs;
extern volatile uint8_t nums;
#endif


#ifdef QUESTION_9
#define ASCII_ZERO 48

//assumes the string size is 10 (one null character)
static void itoa(uint32_t num, char * str, uint8_t base) {
    str[9] = (num % base) + ASCII_ZERO;
    int i;
    for(i = 8; i > -1; i--)
    {
        num = num / base;
        if (num == 0) return;
        str[i] = (num % base) + ASCII_ZERO;
    }
    str[10] = '\0'; //terminate string
}

// Converts a floating point number to string.
static void ftoa(float n, char *str, uint8_t afterpoint)
{
    // Extract integer part
    uint8_t ipart = (uint8_t)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    // convert integer part to string
    int i = intToStr(ipart, str, 0);

    // check for display option after point
    if (afterpoint != 0)
    {
        str[i] = '.';  // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);

        intToStr((uint8_t)fpart, str + i + 1, afterpoint);
    }
}

static void test_itoas(void) {
    char * test = malloc(sizeof(char)*11);
    itoa(12458, test, 10);

    uint32_t test2 = atoi("9734");
}

// reverses a string 'str' of length 'len'
static void reverse(char *str, int len)
{
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}

// Converts a given integer x to string str[].  d is the number
 // of digits required in output. If d is more than the number
 // of digits in x, then 0s are added at the beginning.
uint8_t intToStr(uint32_t x, char *str, uint8_t d)
{
    uint8_t i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return i;
}
#endif
#ifdef QUESTION_11
void characterizeChar(uint8_t data){
    if ((data >= 'A' && data <= 'Z') || (data >= 'a' && data <= 'z')) alphas++;
    if ((data >= 'A' && data <= 'Z') || (data >= 'a' && data <= 'z')) whitespaces++;
    if (data >= '!' && data <= '/' || (data >= ':' && data <= 'z')) puncs++;
    if (data >= '0' && data <= '9') nums++;
}
#endif
