#include <Sensor.h>

void Sensor::shift(){
    for(uint8_t i = 0; i < DIM-1; i++){
        previous_values[i] = previous_values[i+1];
    }
}

float Sensor::filter(float value){
    shift();
    previous_values[DIM-1] = value;
    float aux = 0;
    for(uint8_t i = 0; i < DIM; i++){
        aux += previous_values[i];
    }
    aux = aux / DIM;
    return aux;
}

Sensor::Sensor(uint8_t p){
    pin = p;
    pinMode(pin, INPUT);
    measure_init();
    for(uint8_t i = 0; i < DIM; i++){
        previous_values[i] = 0;
    }
}

void Sensor::measure(){
    uint8_t state = digitalRead(pin);
    if(state != previous_state)
        current_value++; 
    iteration++;
}

float Sensor::get_value(){
    float value = (((float)current_value)/(iteration/2));
    return filter(value);
}

void Sensor::measure_init(){
    current_value = 0;
    iteration = 0;
    previous_state = 0;    
}