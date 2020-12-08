/*
  Скетч к проекту "Многофункциональный RGB светильник"
  Страница проекта (схемы, описания): https://alexgyver.ru/GyverLamp/
  Исходники на GitHub: https://github.com/AlexGyver/GyverLamp/
  Нравится, как написан код? Поддержи автора! https://alexgyver.ru/support_alex/
  Автор: AlexGyver, AlexGyver Technologies, 2019
  https://AlexGyver.ru/
*/

#include "main.h"
#include "brightness.h"
#include "config.h"
#include "effectTicker.h"
#include "encoder.h"
#include <Arduino.h>
#include <EEPROM.h>
#include <FastLED.h>
#include <GyverButton.h>
#include <GyverEncoder.h>

CRGB leds[NUM_LEDS];

GButton button(ENCDR_SW, HIGH_PULL, NORM_OPEN);
Encoder encoder(ENCDR_CLK, ENCDR_DT, ENC_NO_BUTTON, TYPE2);
BrightnessManager brightnessManager;

static const byte maxDim = max(WIDTH, HEIGHT);
MODE_STR modes[MODE_AMOUNT];

int8_t currentMode = 1;
boolean loadingFlag = true;
boolean ONflag = true;
byte setupState = 0; // 0: regular mode (non-setup)
                     // 1: brightness change mode
                     // 2: effect change mode
                     // 3: scale change mode
                     // 4: speed change mode
unsigned long setupState_OffTimer = 0;

unsigned char matrixValue[8][16];

void setup() {
  attachInterrupt(0, interruptEncoderCallback, CHANGE);
  attachInterrupt(1, interruptEncoderCallback, CHANGE);

  FastLED.addLeds<WS2812B, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  if (CURRENT_LIMIT > 0) {
    FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
  }

  FastLED.clear();
  FastLED.show();

  button.setStepTimeout(50);
  button.setClickTimeout(600);
  button.setDebounce(20);

  //Serial.begin(115200);

  if (EEPROM.read(0) == 102) { // если было сохранение настроек, то восстанавливаем их
    currentMode = EEPROM.read(1);
    for (byte x = 0; x < MODE_AMOUNT; x++) {
      modes[x].brightness = EEPROM.read(x * 3 + 11); // (2-10 байт - резерв)
      modes[x].speed = EEPROM.read(x * 3 + 12);
      modes[x].scale = EEPROM.read(x * 3 + 13);
    }
  } else {
    modes[17].brightness = 140;
    modes[1].scale = 1;
  }

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  effectsTick();
  encoderTick();
}
