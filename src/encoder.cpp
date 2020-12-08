#include "encoder.h"
#include "brightness.h"
#include "config.h"
#include "effectTicker.h"
#include "main.h"
#include "utility.h"
#include <Arduino.h>
#include <FastLED.h>
#include <GyverButton.h>
#include <GyverEncoder.h>

extern GButton button;
extern Encoder encoder;
extern boolean ONflag;
extern boolean loadingFlag;
extern int8_t currentMode;
extern MODE_STR modes[MODE_AMOUNT];
extern byte setupState;
extern unsigned long setupState_OffTimer;
extern BrightnessManager brightnessManager;

void interruptEncoderCallback() {
  encoderTick();
}

void encoderTick() {
  button.tick();
  encoder.tick();

  if (button.isSingle()) {
    ONflag = !ONflag;
    changePower();
  }

  if (!ONflag) {
    setupState = 0;
    return;
  }

  if (encoder.isTurn()) {
    if (setupState == 0)
      setupState = 1;

    bool rightDirection = encoder.isRight();

    //  яркость
    if (setupState == 1) {
      if (rightDirection) {
        modes[currentMode].brightness = brightnessManager.getNextBrightnessValue(modes[currentMode].brightness);
      } else {
        modes[currentMode].brightness = brightnessManager.getPreviousBrightnessValue(modes[currentMode].brightness);
      }
    }

    // эффект
    if (setupState == 2) {
      if (rightDirection) {
        if (++currentMode >= MODE_AMOUNT) {
          currentMode = 0;
        }
      } else {
        if (--currentMode < 0) {
          currentMode = MODE_AMOUNT - 1;
        }
      }

      FastLED.setBrightness(modes[currentMode].brightness);
      loadingFlag = true;
      FastLED.clear();
      delay(1);
    }

    // масштаб
    if (setupState == 3) {
      modes[currentMode].scale = constrain(modes[currentMode].scale + 1 * (rightDirection * 2 - 1), 1, 255);
      loadingFlag = true;
      FastLED.clear();
      delay(1);
    }

    // скорость
    if (setupState == 4) {
      modes[currentMode].speed = constrain(modes[currentMode].speed + 12 * (!rightDirection * 2 - 1), 12, 192);
    }

    if (setupState != 0) {
      setupState_OffTimer = millis();
    }
  }

  if (button.hasClicks()) {
    switch (button.getClicks()) {
    case 1:
      setupState = 1;
      break;
    case 2:
      setupState = 2;
      break;
    case 3:
      setupState = 3;
      break;
    case 4:
      setupState = 4;
      break;
    case 8:
      // если было восьмикратное нажатие на кнопку, то производим сброс параметров
      // индикация сброса
      ONflag = false;
      changePower();
      resetConfig();
      delay(200);
      reset();
      break;
    }

    if (setupState != 0) {
      setupState_OffTimer = millis();
    }
  }

  if (setupState != 0 && (millis() - setupState_OffTimer) > SETUP_STATE_TIMEOUT) {
    setupState = 0;
  }

  FastLED.setBrightness(modes[currentMode].brightness);
}
