#include "main.h"
#include "button.h"
#include "effectTicker.h"
#include <Arduino.h>
/*
  Скетч к проекту "Многофункциональный RGB светильник"
  Страница проекта (схемы, описания): https://alexgyver.ru/GyverLamp/
  Исходники на GitHub: https://github.com/AlexGyver/GyverLamp/
  Нравится, как написан код? Поддержи автора! https://alexgyver.ru/support_alex/
  Автор: AlexGyver, AlexGyver Technologies, 2019
  https://AlexGyver.ru/
*/

/*
  Версия 1.4:
  - Исправлен баг при смене режимов
  - Исправлены тормоза в режиме точки доступа
*/

//// Ссылка для менеджера плат:
//// http://arduino.esp8266.com/stable/package_esp8266com_index.json

// ---------------- БИБЛИОТЕКИ -----------------
//#include "timerMinim.h"
#include "config.h"
#include <EEPROM.h>
#include <FastLED.h>
#include <GyverButton.h>

// ------------------- ТИПЫ --------------------
CRGB leds[NUM_LEDS];
// timerMinim timeTimer(3000);
GButton touch(BTN_PIN, LOW_PULL, NORM_OPEN);

// ----------------- ПЕРЕМЕННЫЕ ------------------

// String inputBuffer;
static const byte maxDim = max(WIDTH, HEIGHT);
MODE_STR modes[MODE_AMOUNT];

// struct {
//  boolean state = false;
//  int time = 0;
//} alarm[7];

// byte dawnOffsets[] = {5, 10, 15, 20, 25, 30, 40, 50, 60};
// byte dawnMode;
// boolean dawnFlag = false;
// long thisTime;
// boolean manualOff = false;

int8_t currentMode = 17;
boolean loadingFlag = true;
boolean ONflag = true;
byte numHold;
unsigned long numHold_Timer = 0;
// uint32_t eepromTimer;
// boolean settChanged = false;
// Конфетти, Огонь, Радуга верт., Радуга гориз., Смена цвета,
// Безумие 3D, Облака 3D, Лава 3D, Плазма 3D, Радуга 3D,
// Павлин 3D, Зебра 3D, Лес 3D, Океан 3D,
// colorRoutine, snowRoutine, полосы "Матрица"

unsigned char matrixValue[8][16];

void setup() {

  // ЛЕНТА
  FastLED.addLeds<WS2812B, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS) /*.setCorrection( TypicalLEDStrip )*/;
  FastLED.setBrightness(BRIGHTNESS);
  if (CURRENT_LIMIT > 0) {
    FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
  }
  FastLED.clear();
  FastLED.show();

  touch.setStepTimeout(50);
  touch.setClickTimeout(600);
  touch.setDebounce(20);

  //Serial.begin(115200);
  //Serial.println();

  if (EEPROM.read(0) == 102) { // если было сохранение настроек, то восстанавливаем их (с)НР
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
  // timeTick();
  buttonTick();
  // yield();
}
