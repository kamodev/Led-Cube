// Define all the ports
#define LayerPort    PORTA
#define DataPortB    PORTB
#define DataPortC    PORTC
#define DataPortD    PORTD

// Set the frquency of the clock
#define F_CPU 4000000UL

// All the include for the MCU
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// Mode variable
int led_mode = 1;

// Start up the io ports
static void init(void)
{

    // Set the ouput ports
    DDRA = 0xff;
    DDRB = 0xff;
    DDRC = 0xff;
    DDRD = 0xff;

    // Enable the global interrupts
    sei();
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
    LayerPort = 0xff;
    DataPortB = 0xff;
    DataPortC = 0xff;
    DataPortD = 0xff;
}

// Main loop
int main(void)
{
    // Init the project
    init();

    // Loop forever
    while (1)
    {
        doMode();
    }
}

/*
 * Move the LEDs to the top layer then
 * then randomly drop each one to the
 * lower level
 */
void modeRain()
{
    // This is the cloud layer
    LayerPort = 0x01;

    _delay_ms(500);
}

void modeCycleLayers()
{
    while (LayerPort < 0x09)
    {
        LayerPort << 1;
        _delay_ms(500);
    }
}

/*
 * This function will run the mode that the
 * device is in at the time
 */
void doMode()
{
    switch(led_mode)
    {
        case 1:
            modeRain();
            break;
        case 2:
            modeCycleLayers();
    }
}
