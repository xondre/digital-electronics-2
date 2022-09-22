# Lab 1: ADAM ONDREJKA

### Morse code

1. Listing of C code which repeats one "dot" and one "comma" (BTW, in Morse code it is letter `A`) on a LED. Always use syntax highlighting, meaningful comments, and follow C guidelines:

```c
int main(void)
{
    // Set pin where on-board LED is connected as output
    pinMode(LED_GREEN, OUTPUT);

    // Infinite loop
    while (1)
    {
	//generation of letter 'A' in morse code
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
```

2. Scheme of Morse code application, i.e. connection of AVR device, LED, resistor, and supply voltage. The image can be drawn on a computer or by hand. Always name all components and their values!

   ![diagram]()
