#pragma once
#include <stdint.h>
class GpioSafe {
public:
    static void pinModeSafe(uint8_t pin, uint8_t mode);
};
