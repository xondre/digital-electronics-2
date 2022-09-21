/***********************************************************************
 * 
 * Blink a LED in Arduino-style and use function from the delay library.
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2022 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/


/* Defines -----------------------------------------------------------*/
#define LED_GREEN PB5   // PB5 is AVR pin where green on-board LED 
                        // is connected
//#define LED_RED PB0
#define SHORT_DELAY 250 // Delay in milliseconds
#ifndef F_CPU
# define F_CPU 16000000 // CPU frequency in Hz required for delay funcs
#endif

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>     // AVR device-specific IO definitions
#include <util/delay.h> // Functions for busy-wait delay loops


// -----
// This part is needed to use Arduino functions but also physical pin
// names. We are using Arduino-style just to simplify the first lab.
#include "Arduino.h"
#define PB5 13          // In Arduino world, PB5 is called "13"
//#define PB0 8
// -----


/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Toggle one LED and use delay library.
 * Returns:  none
 **********************************************************************/
int main(void)
{

    // Set pin where on-board LED is connected as output
    pinMode(LED_GREEN, OUTPUT);

    // Infinite loop
    while (1)
    {
        digitalWrite(LED_GREEN, HIGH);  //turn LED on
        _delay_ms(SHORT_DELAY);         //wait for duration of 1 dot
        digitalWrite(LED_GREEN, LOW);   //turn LED off
        _delay_ms(SHORT_DELAY);         //duration between dots and dashes
        digitalWrite(LED_GREEN, HIGH);  
        _delay_ms(SHORT_DELAY*3);       //wait for duration of 1 dash
        digitalWrite(LED_GREEN, LOW);   
        _delay_ms(SHORT_DELAY*3);       //duration between letters is same as dash 

    }

    // Will never reach this
    return 0;
}