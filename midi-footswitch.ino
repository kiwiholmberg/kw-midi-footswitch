/*
 * MIDI footswitch controller using Teensy LC microcontroller.
 * Select USB Type: "MIDI" in the Arduino software when compiling.
 * Created by Kiwi Holmberg 2020
 * MIT Licenced
 */
#include <Bounce.h> // Switch debouncing library

const int channel = 1;  // Used by Teensys MIDI library.
const int PINS[4] = {15, 16, 17, 18};
const int PIN_COUNT = sizeof(PINS) / sizeof(int);
const int MIDICC_NUMBERS[PIN_COUNT] = {60, 61, 62, 63};

const int DEBOUNCE_TIME = 5;

Bounce pins[] = {
  Bounce(PINS[0], DEBOUNCE_TIME),
  Bounce(PINS[1], DEBOUNCE_TIME),
  Bounce(PINS[2], DEBOUNCE_TIME),
  Bounce(PINS[3], DEBOUNCE_TIME)
};

void setup() {
  // Enable the pins with a pullup.
  for (int i=0; i<PIN_COUNT;i++) {
    pinMode(PINS[i], INPUT_PULLUP);
  }
}

void loop() {
  for (int i=0; i<PIN_COUNT;i++) {   
    // Since the switches are latching, and we don't have any use for that in this application
    // just listen for any change in the pin state (simulating a momentary switch)
    if (pins[i].update()) {
      usbMIDI.sendControlChange(MIDICC_NUMBERS[i], 127, channel);
      usbMIDI.sendControlChange(MIDICC_NUMBERS[i], 0, channel);
    }
  }
  
  while (usbMIDI.read()) {
    // Empty the incoming buffer
  }
}
