// All the include for the MCU
#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 4000000UL
#include <util/delay.h>

// Define all the ports
#define DataPortA    PORTC
#define DataPortB    PORTC
#define DataPortC    PORTC
#define DataPortC    PORTD

// Mode variable
int led_mode = 1;

// Change the mode on request
// from button or any other input
void changeMode()
{
    if (led_mode == 10)
    {
        led_mode = 1;
    }
    else
    {
        led_mode++;
    }
}

// Interrupt Service Routine for pin INT0
ISR(INT0_vect)
{
    changeMode();
}

// Main loop
int main(void)
{
    // Set the ouput ports
    DDRA = 0xff;
    DDRB = 0xff;
    DDRC = 0xff;
    DDRD = 0xff;

    // Loop forever
    while (1)
    {

    }
}
