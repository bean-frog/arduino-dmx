/*
Arduino DMX dual LED controller
Uses the Conceptinetics library and DMX shield for the Arduino Uno
*/

#include <Conceptinetics.h>

DMX_Slave dmx_slave(8); // Number of channels. Increase this if you extend the functionality
const int start_addr = 49; //DMX starting address. Change to 1 if this is the first or only fixture in your universe, otherwise update as necessary

// Pin assignments
  // LED 1
  const int led1_redPin = 9;
  const int led1_greenPin = 10;
  const int led1_bluePin = 11;
  // LED 2
  const int led2_redPin = 3;
  const int led2_greenPin = 5;
  const int led2_bluePin = 6;

// DMX channels (relative to the starting address). Rearrange as you like depending on your controller layout.
  // LED 1
  const int led1_intensityDMXch = 1;
  const int led1_redDMXch = 3;
  const int led1_greenDMXch = 4;
  const int led1_blueDMXch = 5;
  // LED 2
  const int led2_intensityDMXch = 2;
  const int led2_redDMXch = 6;
  const int led2_greenDMXch = 7;
  const int led2_blueDMXch = 8;

// Color level variables
  // LED 1
  volatile int led1_redLevel = 0;
  volatile int led1_greenLevel = 0;
  volatile int led1_blueLevel = 0;
  // LED 2
  volatile int led2_redLevel = 0;
  volatile int led2_greenLevel = 0;
  volatile int led2_blueLevel = 0;

void setup()  
{
  dmx_slave.enable();
  dmx_slave.setStartAddress(start_addr);
  
  // Set PWM pins to output
    // LED 1
    pinMode(led1_redPin, OUTPUT);
    pinMode(led1_greenPin, OUTPUT);
    pinMode(led1_bluePin, OUTPUT);
    // LED 2
    pinMode(led2_redPin, OUTPUT);
    pinMode(led2_greenPin, OUTPUT);
    pinMode(led2_bluePin, OUTPUT);
}

void loop()  
{
  // LED 1 controls
  if (dmx_slave.getChannelValue(led1_intensityDMXch) > 0) {

    // Get intensity
    int led1_intensity = dmx_slave.getChannelValue(led1_intensityDMXch);

    // Get channel levels
    led1_redLevel = dmx_slave.getChannelValue(led1_redDMXch);
    led1_greenLevel = dmx_slave.getChannelValue(led1_greenDMXch);
    led1_blueLevel = dmx_slave.getChannelValue(led1_blueDMXch);
    
    // Adjust based on intensity
    led1_redLevel = min(led1_redLevel, led1_intensity);
    led1_greenLevel = min(led1_greenLevel, led1_intensity);
    led1_blueLevel = min(led1_blueLevel, led1_intensity);

    // Write levels to the LED 1 pins
    analogWrite(led1_redPin, led1_redLevel);
    analogWrite(led1_greenPin, led1_greenLevel);
    analogWrite(led1_bluePin, led1_blueLevel);
  } else {
    // LED 1 off
    analogWrite(led1_redPin, 0);
    analogWrite(led1_greenPin, 0);
    analogWrite(led1_bluePin, 0);
  }

  // LED 2 controls
  if (dmx_slave.getChannelValue(led2_intensityDMXch) > 0) {

    // Get intensity
    int led2_intensity = dmx_slave.getChannelValue(led2_intensityDMXch);

    // Get channel levels
    led2_redLevel = dmx_slave.getChannelValue(led2_redDMXch);
    led2_greenLevel = dmx_slave.getChannelValue(led2_greenDMXch);
    led2_blueLevel = dmx_slave.getChannelValue(led2_blueDMXch);
    
    // Adjust based on intensity
    led2_redLevel = min(led2_redLevel, led2_intensity);
    led2_greenLevel = min(led2_greenLevel, led2_intensity);
    led2_blueLevel = min(led2_blueLevel, led2_intensity);

    // Write levels to the LED 2 pins
    analogWrite(led2_redPin, led2_redLevel);
    analogWrite(led2_greenPin, led2_greenLevel);
    analogWrite(led2_bluePin, led2_blueLevel);
  } else {
    // LED 2 off
    analogWrite(led2_redPin, 0);
    analogWrite(led2_greenPin, 0);
    analogWrite(led2_bluePin, 0);
  }
}
