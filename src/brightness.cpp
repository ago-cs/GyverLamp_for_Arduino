#include "brightness.h"
#include <Arduino.h>

uint8_t BrightnessManager::getCurrentLevelIndex(uint8_t currentValue) {
  uint8_t result = 0;
  uint8_t difference = 255;
  for (uint8_t i = 0; i < 16; i++) {
    int d = (uint8_t)abs(currentValue - this->brightnessValues[i]);
    if (d == 0) {
      return i;
    }

    if (d < difference) {
      difference = d;
      result = i;
    }
  }

  return result;
}

uint8_t BrightnessManager::getNextBrightnessValue(uint8_t currentValue) {
  uint8_t index = getCurrentLevelIndex(currentValue);
  if (index < 15)
    index++;

  return this->brightnessValues[index];
}

uint8_t BrightnessManager::getPreviousBrightnessValue(uint8_t currentValue) {
  uint8_t index = getCurrentLevelIndex(currentValue);
  if (index > 0)
    index--;

  return this->brightnessValues[index];
}
