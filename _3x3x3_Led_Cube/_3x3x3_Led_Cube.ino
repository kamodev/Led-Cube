// The mode variable
int mode = 0;

// Patterns 
byte dancingCube[] = {
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000
};

// All the patterns in constants for easier data handling
// The fireworks mode
const byte fireworks[] = {
  {0x00, 0x01, 0x02},
  {0x00, 0x01, 0x02},
  {0x00, 0x01, 0x02},
  {0x00, 0x01, 0x02},
  {0x00, 0x01, 0x02},
  {0x00, 0x01, 0x02},
};

// This will be one color chasing the other
// color all throughout the cube
const byte pacman[] = {
  {0x00, 0x01, 0x02},
  {0x00, 0x01, 0x02},
  {0x00, 0x01, 0x02},
  {0x00, 0x01, 0x02},
  {0x00, 0x01, 0x02},
  {0x00, 0x01, 0x02},
};

const byte outlinecube[] = {
  {0x00, 0x01, 0x02},
  {0x00, 0x01, 0x02},
  {0x00, 0x01, 0x02},
  {0x00, 0x01, 0x02},
  {0x00, 0x01, 0x02},
  {0x00, 0x01, 0x02},
};

// Setup the device for use
void setup()
{
  // Set the ports to OUTPUT
  DDRB = 0xff;
  DDRC = 0xff;
  DDRD = 0xff;

  // Attach Interrupts
  attachInterrupt(0, intrNLight, RISING);         // Add night light switch
  attachInterrupt(1, intrChangeMode, FALLING;     // Add change mode button
}

// Main program
void loop()
{
  // Repeat the cureent mode over and over
  doMode();
}

// All the Interrupt handlers
// Night light mode
void intrNLight()
{
  // TODO: Add code for this mode
  PORTB = 0xff;
  PORTC = 0xff;
  PORTD = 0xff;
  mode = 10;
}

// Change mode of the cube
void intrChangeMode()
{
  if (mode != 10)   // The night light is on
  {
    if (mode >= 9)  // Time to reset
    {
      mode = 0;
    }
    else
    {
      mode++;
    }
  }
}

// All of the different modes
void doMode()
{
  switch(mode)
  {
    case 0:
      // TODO: Mode
      break;

    case 1:
      // TODO: Mode
      break;

    case 2:
      // TODO: Mode
      break;

    case 3:
      // TODO: Mode
      break;

    case 4:
      // TODO: Mode
      break;

    case 5:
      // TODO: Mode
      break;

    case 6:
      // TODO: Mode
      break;

    case 7:
      // TODO: Mode
      break;

    case 8:
      // TODO: Mode
      break;

    case 9:
      // TODO: Mode
      break;
  }
}

// This mode will chase a different
// color LED all the way through the cube
void modePacMan()
{
  // TODO: finish the mode
}

// Mode: Display fireworks
void modeFireWorks()
{
  // TODO: Finish the account
}

void playDancingCube()
{
  
}