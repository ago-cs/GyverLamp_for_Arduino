#include "config.h"
#include "effects.h"
#include "main.h"
#include "noiseEffects.h"
#include "utility.h"
#include <Arduino.h>

uint32_t effTimer;
byte ind;

extern boolean ONflag;
extern int8_t currentMode;
extern byte numHold;
extern MODE_STR modes[MODE_AMOUNT];

void effectsTick() {
  // if (!dawnFlag)
  {
    if (ONflag && millis() - effTimer >= ((currentMode < 5 || currentMode > 13) ? modes[currentMode].speed : 50)) {
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
        //      case 17:
        //        lightersRoutine();
        break;
      }
      switch (numHold) { // индикатор уровня яркости/скорости/масштаба
      case 1:
        ind = (modes[currentMode].brightness + 1) / 12;
        for (byte y = 0; y < HEIGHT; y++) {
          if (ind > y) {
            drawPixelXY(7, y, CHSV(10, 255, 255));
            drawPixelXY(8, y, CHSV(10, 255, 255));
          } else {
            drawPixelXY(7, y, 0);
            drawPixelXY(8, y, 0);
          }
        }
        break;
      case 2:
        ind = (modes[currentMode].speed - 1) * 16 / 60;
        for (byte y = 0; y <= HEIGHT; y++) {
          if (ind <= y) {
            drawPixelXY(7, 15 - y, CHSV(100, 255, 255));
            drawPixelXY(8, 15 - y, CHSV(100, 255, 255));
          } else {
            drawPixelXY(7, 15 - y, 0);
            drawPixelXY(8, 15 - y, 0);
          }
        }
        break;
      case 3:
        ind = (modes[currentMode].scale + 1) / 12;
        for (byte y = 0; y < HEIGHT; y++) {
          if (ind > y) {
            drawPixelXY(7, y, CHSV(150, 255, 255));
            drawPixelXY(7, y, CHSV(150, 255, 255));
          } else {
            drawPixelXY(7, y, 0);
            drawPixelXY(8, y, 0);
          }
        }
        break;
      }
      FastLED.show();
    }
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
