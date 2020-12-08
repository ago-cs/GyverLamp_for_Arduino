#include <stdint.h>

class BrightnessManager {
private:
  const uint8_t brightnessValues[16] = {
      3, 6, 10, 15, 21, 28, 36, 45, 55, 67, 81, 97, 117, 139, 164, 192};

public:
  uint8_t getNextBrightnessValue(uint8_t currentValue);
  uint8_t getPreviousBrightnessValue(uint8_t currentValue);
  uint8_t getCurrentLevelIndex(uint8_t currentValue);
};
