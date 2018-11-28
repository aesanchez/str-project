#include <Arduino.h>
#define DIM 5
class Sensor
{
    uint8_t pin;
    uint8_t current_value;
    uint8_t iteration;
    uint8_t i;
    float aux;
    //para el filtro
    float previous_values[DIM];
  public:
    Sensor(uint8_t pin);
    void measure_tick();
    float get_value();
    void measure_init();
  private:
    float filter(float);
    void shift();    
};