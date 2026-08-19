/*
      DiceCard - ATtiny1614-SSN
-------------------------------------

Code for my Dice Card, first time using the chip itself instead of a microcontroller board :P

PIN MAP:
    D1  = PA2      D6  = PA7
    D2  = PA3      D7  = PB3
    D3  = PA4      D8  = PB2
    D4  = PA5      D9  = PB1
    D5  = PA6      D10 = PB0
    Button = PA1 (button to GND, internal pull-up, active LOW)
    PA0 = UPDI (not used as GPIO)
*/




#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#define D100_TENS_UNITS METHOD true

const uint16_t LONG_PRESS_MS = 550;
const uint16_t DEBOUNCE_MS = 25;

// Pins
const uint8_t ledPins[10] = {
  PIN_PA2, // D1
  PIN_PA3, // D2
  PIN_PA4, // D3
  PIN_PA5, // D4
  PIN_PA6, // D5
  PIN_PA7, // D6
  PIN_PB3, // D7
  PIN_PB2, // D8
  PIN_PB1, // D9
  PIN_PB0  // D10
};
const uint8_t BTN = PIN_PA1;

// Selectable Die
const uint8_t dieOptions[7] = {1, 2, 4, 6, 8, 9, 10};
const uint8_t NUM_OPTIONS = 7;

// Methods

void allOff(){
  for(uint16_t i = 0; i<10; i++) digitalWrite(ledPins[i], LOW);
}

void allOn(){
  for(uint16_t i = 0; i<10; i++) digitalWrite(ledPins[i], HIGH);
}

void lightOnly(uint8_t idx){
  for (uint8_t i = 0; i < 10; i++) digitalWrite(ledPins[i], i == idx ? HIGH : LOW);
}

bool buttonPressed(){
  return digitalRead(BTN) == LOW;
}

void waitForPressStart(){ while (!buttonPressed()) { /* spin */ }
  delay(DEBOUNCE_MS);
  while (!buttonPressed()) { /* debounce glitch, keep waiting */ }
}

// Blocks until either the button is released before LONG_PRESS MS -> returns false
// or the hold time reaches LONG_PRESS_MS -> returns true immediately
bool waitForPressOutcome() {
  waitForPressStart();
  uint32_t start = millis();
  while (buttonPressed()) {
    if (millis() - start >= LONG_PRESS_MS) {
      return true; // long press threshold reached -> go roll now
    }
  }
  delay(DEBOUNCE_MS);
  return false; // released early -> short press
}

// sleepy eepy
volatile bool wokeUp = false;

void wakeISR(){
  wokeUp = true;
}

void goToSleep() {
  allOff();
  wokeUp = false;

  attachInterrupt(digitalPinToInterrupt(BTN), wakeISR, FALLING);

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  cli();
  sleep_enable();
  sei();
  sleep_cpu();      // <-- CPU halts here until button press wakes it, because energy saving :>
  sleep_disable();

  detachInterrupt(digitalPinToInterrupt(BTN));

  // debounce the waking press, then wait for it to be released
  // before we start listening for menu presses.
  delay(DEBOUNCE_MS);
  while (buttonPressed()) { /* wait out the wake press */ }
  delay(DEBOUNCE_MS);
}

// Animations
// Rolls a "faces"-sided die, declaring the chase.
// goes to the result and holds 2 secs. Then it turns off.
uint8_t rollAndShow(uint8_t faces) {
  uint8_t resultIdx = random(0, faces); // 0..faces-1

  const uint8_t loops = 3; // full spins before landing
  uint16_t totalSteps = (uint16_t)loops * faces + resultIdx + 1;

  for (uint16_t i = 0; i < totalSteps; i++) {
    uint8_t idx = i % faces;
    lightOnly(idx);

    uint16_t remaining = totalSteps - i;
    uint16_t d = map(remaining, 1, totalSteps, 220, 35); // decelerate
    delay(d);
  }

  lightOnly(resultIdx);
  delay(2000);
  allOff();

  return resultIdx + 1;
}

void performRoll(uint8_t dieCode){
  if(dieCode == 1){
    // Special case d20 -> two d10s, youre gonna read the sum
    rollAndShow(10);
    delay(150);
    rollAndShow(10);
  }else if (dieCode == 9) {
    #if D100_TENS_UNITS_METHOD
        // SPECIAL: d100 => tens-digit roll (0-9, shown as faces 1-10 wher
        rollAndShow(10);
        delay(150);
        rollAndShow(10);
    #else
        // literal spec: two d10 rolls, reader adds them together
        rollAndShow(10);
        delay(150);
        rollAndShow(10);
    #endif
      } else {
        // normal die: dieCode itself is the number of faces
        rollAndShow(dieCode);
      }
}

// Setup and loop
void setup(){
  for(uint8_t i = 0; i < 10 ; i++) pinMode(ledPins[i], OUTPUT);
  allOff();
  pinMode(BTN, INPUT_PULLUP);
}

void loop(){
  goToSleep();
  randomSeed(micros());

  allOn();
  delay(600);
  allOff();
  delay(150);

  // Selection "menu"-thing
  uint8_t selection = 0;
  while(true){
      lightOnly(selection); // show current with corresponding LED
    bool longPress = waitForPressOutcome();

    if (longPress) {
      break; // hold -> roll this die now
    } else {
      selection = (selection + 1) % NUM_OPTIONS; // short press -> next option
    }
  }

  allOff();
  delay(150);

  // roll this thing :D
  performRoll(dieOptions[selection]);

  // loops back to Sleep
}