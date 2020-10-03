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
      modes[currentMode].brightness = constrain(modes[currentMode].brightness + 2 * (rightDirection * 2 - 1), 1, 192);
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
      modes[currentMode].scale = constrain(modes[currentMode].scale + 2 * (rightDirection * 2 - 1), 1, 192);
    }

    // скорость
    if (setupState == 4) {
      modes[currentMode].speed = constrain(modes[currentMode].speed + 1 * (rightDirection * 2 - 1), 1, 60);
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
    case 5:
      // если было пятикратное нажатие на кнопку, то производим сброс параметров
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
