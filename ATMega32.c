#define F_CPU 11059200UL

#include "avr/io.h"
#include <avr/interrupt.h>
#include "stdio.h"
#include <util/delay.h>

volatile double AdcOutput;
volatile unsigned char Temp,Temp1,Temp2;
volatile unsigned int k;

/************************************************
SPI INITIALISATION
*************************************************/

void SPIinit(void)
{
    DDRB |= (1<<PB4)|(1<<PB5) | (1<<PB7); // Set MOSI , SCK , and SS output
    SPCR |= ((1<<SPE)|(1<<MSTR)|(1<<SPR1)|(1<<SPR0)); // Enable SPI, Master, set clock rate fck/128

}

/************************************************
Writetoreg
*************************************************/

void Writetoreg( int byteword)
{
    SPDR = byteword; // put the byteword into data register
    while(!(SPSR & (1<<SPIF))); // Wait for transmission complete
    byteword=SPDR; //just for clearing spif
}


/************************************************
Read
*************************************************/

unsigned int Read(char reglength)
{
    int b;
    for(b=0;b<reglength;b++)
    {
        SPDR = 0xFF;
        while(!(SPSR &(1<<SPIF))); // Wait for transmission complete
        if(b==0)
        {
            k=SPDR*256;
        }
        else
        k=k+SPDR;
    }

    return k;
}

/************************************************
ADC INITIALISATION
*************************************************/

void ADCinit(void)
{
SPIinit();
Writetoreg(0x20); //Active channel is Ain(+) Ain(-), next operation as write to clock register
Writetoreg(0x0B); //(for clock register) master clock enabled, 2MHz Clock, set output rate to 20Hz*///0x08
Writetoreg(0x10); //Active channel is Ain1(+) Ain1(-), next operation as write to the setup register
Writetoreg(0x44); //(for setup register) gain = 1, bipolar mode, buffer off, clear FSYNC and perform a Self Calibration*/
}

/************************************************
Lcd out
*************************************************/

void lcdout(unsigned char Temp)
{
PORTA &= 0b11101111; // LOW TO PA4 'E' PIN

Temp1 = Temp; // EXAMPLE VALUE 25
Temp2 = Temp1;
Temp2 = Temp2 >>4; // ,, 02

Temp2 = Temp2 & 0x0F; // 1011 + 2

Temp = (PORTA);
Temp = Temp & 0xF0;
Temp = Temp | Temp2; // 1011 + 2
PORTA = Temp;


PORTA |= 0b00010000;
PORTA &= 0b11101111;


Temp = Temp1; // 25
Temp2 = Temp;
Temp2 = Temp2 & 0x0F; // 05
Temp = (PORTA); // 1011+5
Temp = Temp & 0xF0; // 1011+5
Temp = Temp | Temp2;
PORTA = Temp;
PORTA |= 0b00010000;
PORTA &= 0b11101111;
_delay_us (50);
}
/************************************************
lcd initialisation
*************************************************/

void LcdInit(void)
{
    DDRA = 0xFF;
    PORTA &= 0b11011111;
    _delay_ms (20);
    lcdout(0x38);
    _delay_ms (05);
    lcdout(0x38);
    _delay_ms (100);
    lcdout(0x38);
    _delay_ms (02);
    lcdout(0x28);
    _delay_ms (02);
    lcdout(0x08);
    _delay_ms (02);
    lcdout(0x01);
    _delay_ms (02);
    lcdout(0x06);
    _delay_ms (02);
    lcdout(0x0F);
    _delay_ms (02);
    lcdout(0x0C);
    _delay_ms (02);
}


void calculate(volatile double data)
{
    volatile double data2;

    data = data * 2.5 /65535;

    Temp = data;
    lcdout(Temp|0x30);
    lcdout('.');

    Temp = data*100;
    Temp =(Temp/10)%10;
    lcdout(Temp|0x30);

    Temp = data*100;
    Temp =(Temp%10);
    lcdout(Temp|0x30);

    data2 = data*1000;
    Temp =((int)data2%10);
    lcdout(Temp|0x30);

    data = data*10000;
    Temp =((int)data%10);
    lcdout(Temp|0x30);

}
void display_number(volatile long num)
{
    int num3;

    num3=num/10000;
    lcdout(num3|0x30);
    num =num%10000;

    num3 =num/1000;
    lcdout(num3|0x30);
    num =(int)num%1000;

    num3 =num/100;
    lcdout(num3|0x30);
    num =(int)num%100;

    num3 =num/10;
    lcdout(num3|0x30);
    num3 =(int)num%10;

    lcdout(num3|0x30);
}

/************************************************
Main loop
*************************************************/

int main()
{
    DDRA = 0xFF; //Config DDRA as O/P for LCD display

    DDRC = 0x40; //Config PC6 o/p for laser
    PORTC |= 0x40;

    LcdInit(); //lcd initialization
    ADCinit(); //adc initialization

    for(;;)
    {
        do
        {
            Writetoreg(0x08);
            Read(1);
        }
        while(k&0x80);

        // read from adc
        Writetoreg(0x38); //set the next operation for 16 bit read from the data register
        AdcOutput = Read(2);
        _delay_ms (1000);
        PORTA &= 0b11011111;
        lcdout(0x0C5);
        PORTA |= 0b00100000;
        calculate(AdcOutput);
    }
    return 0;
}