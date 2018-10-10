#include <Arduino.h>
#define DIM 10
class Sensor
{
    uint8_t pin;
    uint8_t current_value;
    uint8_t iteration;
    float previous_values[DIM];
    uint8_t previous_state;
  public:
    Sensor(uint8_t pin);
    void measure();
    float get_value();
    void measure_init();
  private:
    float filter(float);
    void shift();
};