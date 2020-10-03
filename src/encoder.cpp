#include "config.h"
#include "effectTicker.h"
#include "main.h"
#include "utility.h"
#include <Arduino.h>
#include <FastLED.h>
#include <GyverButton.h>
#include <GyverEncoder.h>

extern GButton touch;
extern Encoder encoder;
extern boolean ONflag;
extern boolean loadingFlag;
extern int8_t currentMode;
extern MODE_STR modes[MODE_AMOUNT];
extern byte numHold;
extern unsigned long numHold_Timer;

// 0: regular mode (non-setup)
// 1: brightness change mode
// 2: effect change mode
// 3: scale change mode
// 4: freequency change mode
extern int setupModeState = 0;
extern unsigned long setupModeMillis;

boolean brightDirection, speedDirection, scaleDirection;
// byte numHold;

void encoderTick() {
  touch.tick();
  encoder.tick();

  if (touch.isSingle()) {
    ONflag = !ONflag;
    changePower();
  }

  if (!ONflag)
    return;

  if (encoder.isTurn()) {
    if (setupModeState == 0)
      setupModeState = 1;

    if (setupModeState == 1) {
      bool brightDirectionAgo = encoder.isRight();
      modes[currentMode].brightness = constrain(modes[currentMode].brightness + 2 * (brightDirectionAgo * 2 - 1), 1, 192);
      numHold = 1;
    }
  }

  if (touch.isDouble()) {
    if (++currentMode >= MODE_AMOUNT)
      currentMode = 0;
    FastLED.setBrightness(modes[currentMode].brightness);
    loadingFlag = true;
    // settChanged = true;
    FastLED.clear();
    delay(1);
  }
  if (touch.isTriple()) {
    if (--currentMode < 0)
      currentMode = MODE_AMOUNT - 1;
    FastLED.setBrightness(modes[currentMode].brightness);
    loadingFlag = true;
    // settChanged = true;
    FastLED.clear();
    delay(1);
  }

  if ((touch.hasClicks()) && (touch.getClicks() == 5)) {
    // если было пятикратное нажатие на кнопку, то производим сброс параметров && (touch.hasClicks())
    // индикация сброса
    ONflag = false;
    changePower();
    resetConfig();
    delay(200);
    reset();
  }

  if (touch.isHolded()) { // изменение яркости при удержании кнопки
    brightDirection = !brightDirection;
    numHold = 1;
  }

  if (touch.isHolded2()) { // изменение скорости "speed" при двойном нажатии и
                           // удержании кнопки
    speedDirection = !speedDirection;
    numHold = 2;
  }

  if (touch.isHolded3()) { // изменение масштаба "scale" при тройном нажатии и
                           // удержании кнопки
    scaleDirection = !scaleDirection;
    numHold = 3;
  }

  if (touch.isStep()) {
    if (numHold != 0) {
      numHold_Timer = millis();
    }
    loadingFlag = true;
    switch (numHold) {
    case 1:
      modes[currentMode].brightness = constrain(modes[currentMode].brightness + 2 * (brightDirection * 2 - 1), 1, 192);
      break;

    case 2:
      modes[currentMode].speed = constrain(modes[currentMode].speed + 1 * (speedDirection * 2 - 1), 1, 60);
      break;

    case 3:
      modes[currentMode].scale = constrain(modes[currentMode].scale + 2 * (scaleDirection * 2 - 1), 1, 192);
      break;
    }
  }
  if ((millis() - numHold_Timer) > numHold_Time) {
    numHold = 0;
    numHold_Timer = millis();
  }
  FastLED.setBrightness(modes[currentMode].brightness);
}
