#include <Arduino.h>
#include <Sensor.h>

#define SENSOR_PIN_1 3
#define SENSOR_PIN_2 2
#define SAMPLE_STEP_PERIOD 1 //in miliseconds
#define SAMPLE_PERIOD 20

Sensor sensor1 (SENSOR_PIN_1);
Sensor sensor2 (SENSOR_PIN_2);

void setup(){
  Serial.begin(115200);
}
void loop(){
    sensor1.measure_init();
    sensor2.measure_init();
    for(uint8_t i = 0; i < SAMPLE_PERIOD; i+=SAMPLE_STEP_PERIOD){
        sensor1.measure();
        sensor2.measure();
        delay(SAMPLE_STEP_PERIOD);
    }
    Serial.print(sensor1.get_value());
    Serial.print("/");
    Serial.println(sensor2.get_value());  
}