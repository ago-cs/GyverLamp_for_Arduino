#pragma once
#include <Arduino.h>
#include <FastLED.h>

void fillAll(CRGB color);
void drawPixelXY(int8_t x, int8_t y, CRGB color);
uint32_t getPixColor(int thisSegm);
uint32_t getPixColorXY(int8_t x, int8_t y);
uint16_t getPixelNumber(int8_t x, int8_t y);
void saveConfig();
void resetConfig();
void reset();
