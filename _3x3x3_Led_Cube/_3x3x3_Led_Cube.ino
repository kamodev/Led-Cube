int mode = 0;

// Setup the device for use
void setup()
{
  // Set the ports
  PORTB = B11111111;
  PORTC = B00000000;
  PORTD = B10100101;

  // Attach Interrupts
  attachInterrupt(0, intrNLight, RISING);    // Add night light switch
  attachInterrupt(1, intrChangeMode, FALLING;    // Add change mode button
  attachInterrupt(2, intrRndMode, FALLING);    // Add random mode button
}

// Main program
void loop()
{

}

// All the Interrupt handlers
// Night light mode
void intrNLight()
{
  // TODO: Add code for this mode
}

// Random pattern mode
void intrRndMode()
{
  mode = 9;
}

// Change mode of the cube
void intrChangeMode()
{
  if (mode == 8)
  {
    mode = 0;
  }
  else
  {
    mode++;
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