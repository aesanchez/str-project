#include <Sensor.h>

Sensor::Sensor(uint8_t p){
    pin = p;
    pinMode(pin, INPUT);
    measure_init();
}

void Sensor::measure(){
    current_value += digitalRead(pin);
    iteration++;
}

float Sensor::get_value(){
    return ((float)current_value)/iteration;
}

void Sensor::measure_init(){
    current_value = 0;
    iteration = 0;
}