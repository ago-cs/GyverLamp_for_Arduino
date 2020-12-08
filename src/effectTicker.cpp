#include "brightness.h"
#include "config.h"
#include "effects.h"
#include "main.h"
#include "noiseEffects.h"
#include "utility.h"
#include <Arduino.h>

uint32_t effTimer;
byte index;
byte index2;

extern boolean ONflag;
extern int8_t currentMode;
extern byte setupState;
extern MODE_STR modes[MODE_AMOUNT];
extern BrightnessManager brightnessManager;

void effectsTick() {
  //if (ONflag && millis() - effTimer >= ((currentMode < 5 || currentMode > 13) ? modes[currentMode].speed : 50)) {
  if (ONflag && millis() - effTimer >= modes[currentMode].speed) {
    effTimer = millis();
    switch (currentMode) {
    case 0:
      sparklesRoutine();
      break;
    case 1:
      fireRoutine();
      break;
    case 2:
      rainbowVertical();
      break;
    case 3:
      rainbowHorizontal();
      break;
    case 4:
      colorsRoutine();
      break;
    case 5:
      madnessNoise();
      break;
    case 6:
      cloudNoise();
      break;
    case 7:
      lavaNoise();
      break;
    case 8:
      plasmaNoise();
      break;
    case 9:
      rainbowNoise();
      break;
    case 10:
      rainbowStripeNoise();
      break;
    case 11:
      zebraNoise();
      break;
    case 12:
      forestNoise();
      break;
    case 13:
      oceanNoise();
      break;
    case 14:
      colorRoutine();
      break;
    case 15:
      snowRoutine();
      break;
    case 16:
      matrixRoutine();
      break;
    case 17:
      whiteLamp();
      break;
    }
    switch (setupState) {
    case 1: // индикатор уровня яркости
      index = brightnessManager.getCurrentLevelIndex(modes[currentMode].brightness);
      for (byte y = 0; y < HEIGHT; y++) {
        if (index >= y) {
          drawPixelXY(7, y, CHSV(10, 255, 255));
          drawPixelXY(8, y, CHSV(10, 255, 255));
        } else {
          drawPixelXY(7, y, 0);
          drawPixelXY(8, y, 0);
        }
      }
      break;
    case 2: // индикатор переключения режима
      for (byte x = 0; x < WIDTH; x++) {
        drawPixelXY(x, 0, CHSV(255, 255, 255));
        drawPixelXY(x, 1, 0);
      }
      break;
    case 3:                                   // индикатор регулировки "масштаба"
      index = modes[currentMode].scale / 16;  // шкала шестнадцаток
      index2 = modes[currentMode].scale % 16; // шкала единц

      drawPixelXY(7, 0, CHSV(170, 255, 255)); // первая линия исключается,
      drawPixelXY(8, 0, CHSV(170, 255, 0));   // так как для отображения 255 значений
      drawPixelXY(9, 0, CHSV(170, 255, 255)); // нужно всего два ряда по 15

      for (byte y = 1; y <= HEIGHT + 1; y++) {
        drawPixelXY(7, HEIGHT - y, index <= y ? CHSV(170, 255, 255) : CHSV(0, 0, 0));
        drawPixelXY(8, HEIGHT - y, CHSV(0, 0, 0));
        drawPixelXY(9, HEIGHT - y, index2 <= y ? CHSV(170, 255, 255) : CHSV(0, 0, 0));
      }

      break;
    case 4: // индикатор уровня скорости (зелёный)
      index = modes[currentMode].speed / 12 - 1;
      for (byte y = 0; y <= HEIGHT; y++) {
        drawPixelXY(7, 15 - y, index <= y ? CHSV(80, 255, 255) : CHSV(0, 0, 0));
        drawPixelXY(8, 15 - y, index <= y ? CHSV(80, 255, 255) : CHSV(0, 0, 0));
        drawPixelXY(9, 15 - y, index <= y ? CHSV(80, 255, 255) : CHSV(0, 0, 0));
      }
      break;
    }
    FastLED.show();
  }
}

void changePower() { // плавное включение/выключение
  if (ONflag) {
    effectsTick();

    for (int i = 0; i < modes[currentMode].brightness; i += 8) {
      FastLED.setBrightness(i);
      delay(1);
      FastLED.show();
    }

    FastLED.setBrightness(modes[currentMode].brightness);
    delay(2);
    FastLED.show();
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    effectsTick();

    for (int i = modes[currentMode].brightness; i > 8; i -= 8) {
      FastLED.setBrightness(i);
      delay(1);
      FastLED.show();
    }

    FastLED.clear();
    delay(2);

    FastLED.show();

    saveConfig();
    digitalWrite(LED_BUILTIN, LOW);
  }
}
