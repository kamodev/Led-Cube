// All the include for the MCU
#include <avr/io.h>
#include <avr/interrupt.h>

// Set the frquency of the clock
#define F_CPU 4000000UL
#include <util/delay.h>

// Define all the ports
#define DataPortA    PORTC
#define DataPortB    PORTC
#define DataPortC    PORTC
#define DataPortC    PORTD

// Mode variable
int led_mode = 1;

// Start up the io ports
static void ioinit(void)
{

}

// Change the mode on request
// from button or any other input
void changeMode()
{
    led_mode++;

    if (led_mode >= 10)
    {
        led_mode = 1;
    }
}

// Interrupt Service Routine for pin INT0
ISR(INT0_vect)
{
    changeMode();
}

// Night light mode
ISR(INT1_vect)
{

}

// Main loop
int main(void)
{
    // Set the ouput ports
    DDRA = 0xff;
    DDRB = 0xff;
    DDRC = 0xff;
    DDRD = 0xff;

    // Init the IO
    ioinit();

    // Loop forever
    while (1)
    {

    }
}
