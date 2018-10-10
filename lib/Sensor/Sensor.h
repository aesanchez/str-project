#include <Arduino.h>
class Sensor
{
    uint8_t pin;
    uint8_t current_value;
    uint8_t iteration;
  public:
    Sensor(uint8_t pin);
    void measure();
    float get_value();
    void measure_init();
};