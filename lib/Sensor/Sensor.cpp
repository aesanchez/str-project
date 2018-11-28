#include <Sensor.h>

void Sensor::shift(){
    for(i = 0; i < DIM-1; i++){
        previous_values[i] = previous_values[i+1];
    }
}

float Sensor::filter(float value){
    shift();
    previous_values[DIM-1] = value;
    aux = 0;
    for(i = 0; i < DIM; i++){
        aux += previous_values[i];
    }
    aux = aux / DIM;
    return aux;
}

Sensor::Sensor(uint8_t p){
    pin = p;
    pinMode(pin, INPUT);
    measure_init();
    for(i = 0; i < DIM; i++){
        previous_values[i] = 0;
    }
}
void Sensor::measure_tick(){
    if(digitalRead(pin))
        current_value++;
    iteration++;
}

float Sensor::get_value(){
    return filter(((float)current_value)/(iteration));
}

void Sensor::measure_init(){
    current_value = 0;
    iteration = 0;  
}