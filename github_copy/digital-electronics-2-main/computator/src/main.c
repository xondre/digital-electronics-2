/* Defines -----------------------------------------------------------*/
#define CLK PB3   //main output from rotary encoder                   
#define DT PB4    //reference output from rotary encoder
#define SW_ENC PB5  //button output from rotary encoder
#define SW_JS PD3   //button output from joystick

#ifndef F_CPU
# define F_CPU 16000000 // CPU frequency in Hz required for delay funcs
#endif

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>     // AVR device-specific IO definitions
#include <util/delay.h> // Functions for busy-wait delay loops
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <gpio.h>           // GPIO library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <lcd.h>            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for number conversions

/*  Global variables         */
uint16_t x_axis = 512;  //
uint16_t y_axis = 512;  //
uint8_t axis_select = 0;    //
uint16_t O = 0;   //circumference
uint16_t S = 0;   //area
uint8_t a1 = 0;
uint8_t b1 = 0;
uint8_t encoder_ref = 0;
uint8_t line1_pos = 0;


/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Toggle LEDs and use delay library.
 * Returns:  none
 **********************************************************************/
uint8_t get_joystick(void)
    { 
      uint8_t position = 0; 
      for(uint8_t i = 0; i < 2; i++)
      {
        if(i == 0)
        {
        // set ADC output variable to x axis
          axis_select = 0;
        // Select input channel ADC0 for x axis
          ADMUX &= ~((1<<MUX0) | (1<<MUX1) | (1<<MUX2) | (1<<MUX3));
        // Start ADC conversion
          ADCSRA |= (1<<ADSC);
          _delay_us(125);
        }
        else
        {
        // set ADC output variable to y axis
          axis_select = 1;
        // Select input channel ADC1 for y axis
          ADMUX |= (1<<MUX0);  ADMUX &= ~((1<<MUX1) | (1<<MUX2) | (1<<MUX3));
        // Start ADC conversion
          ADCSRA |= (1<<ADSC);
        }
      }

      if(x_axis < 400)
        position = 4;
      else if(y_axis > 625)
        position = 1;
      else if(y_axis < 400)
        position = 3;
      else if(x_axis > 625)
        position = 2;
      else
        position = 0;

      return position;
    }

int8_t get_encoder(void)
    {
      int8_t step = 0;
      uint8_t clk_val = GPIO_read(&PINB, CLK);

      if(clk_val != encoder_ref){ 
        if(GPIO_read(&PINB, DT) != clk_val)
          step = -1;
        else
          step = 1;
      }else
          step = 0;
      
      encoder_ref = clk_val;
      return step;
    }

int main(void)
{   
  
    GPIO_mode_input_nopull(&DDRB, CLK);
    GPIO_mode_input_nopull(&DDRB, DT);
    GPIO_mode_input_pullup(&DDRB, SW_ENC);
    GPIO_mode_input_pullup(&DDRD, SW_JS);
    encoder_ref = GPIO_read(&PINB, CLK);
    
    lcd_init(LCD_DISP_ON_BLINK);
    lcd_gotoxy(0,0);
    lcd_puts("A=");
    lcd_gotoxy(5,0);
    lcd_puts("B=");
    lcd_gotoxy(0,1);
    lcd_puts("O=");
    lcd_gotoxy(6,1);
    lcd_puts("S=");

    //TIM1_overflow_262ms();
    //TIM1_overflow_interrupt_enable();
    
    // Configure Analog-to-Digital Convertion unit
    // Select ADC voltage reference to "AVcc with external capacitor at AREF pin"
    ADMUX |= (1<<REFS0);  //setting REFS0 to 1
    ADMUX &= ~(1<<REFS1); //setting REFS1 to 0
    // Enable ADC module
    ADCSRA |= (1<<ADEN);
    // Enable conversion complete interrupt
    ADCSRA |= (1<<ADIE);
    // Set clock prescaler to 128
    ADCSRA |= ((1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2));

    // Enables interrupts by setting the global interrupt mask
    sei();
     
    
    // Infinite loop
    while (1)
    {   
      char string;
        if(get_joystick() == 3)
          line1_pos = 1;
        else if(get_joystick() == 1)
          line1_pos = 0;

        if (line1_pos==0)
        {
          lcd_gotoxy(2,0);
          itoa(a1, string, 10);
          lcd_puts(string);
          lcd_gotoxy(2,0);
          a1 += get_encoder();
          if (a1 >= 0 )
          else if (a1 )
        }
        else
        {
          lcd_gotoxy(7,0);
          itoa(b1, string, 10);
          lcd_puts(string);
          lcd_gotoxy(7,0);
          b1 += get_encoder();
        }
      char result[4];
      O = 2*a1 + 2*b1;
      S = a1 * b1;
      itoa(O, result, 10);
      lcd_gotoxy(2,1);
      lcd_puts("    ");
      lcd_gotoxy(2,1);
      lcd_puts(result);
      itoa(S, result, 10);
      lcd_gotoxy(8,1);
      lcd_puts("    ");
      lcd_gotoxy(8,1);
      lcd_puts(result);
      if(line1_pos==0)
        lcd_gotoxy(2,0);
      else
        lcd_gotoxy(7,0);

      _delay_ms(20);
    }    
    return 0;

    

}

/* Interrupt service routines ----------------------------------------*/
//ISR(TIM1_OVF_vect)
//{
      
//}

/**********************************************************************
 * Function: ADC complete interrupt
 * Purpose:  Display converted value on LCD screen.
 **********************************************************************/
ISR(ADC_vect)
{   
  if(axis_select == 0)
    x_axis = ADC;
  else 
    y_axis = ADC;
}