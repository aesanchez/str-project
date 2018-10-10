#include <Arduino.h>
#include <Sensor.h>

#define SENSOR_PIN_1 2
#define SENSOR_PIN_2 4
#define SENSOR_PIN_3 5
#define SAMPLE_STEP_PERIOD 1 //in miliseconds
#define SAMPLE_PERIOD 100

Sensor sensor1 (SENSOR_PIN_1);
Sensor sensor2 (SENSOR_PIN_2);
Sensor sensor3 (SENSOR_PIN_3);

void setup(){
  Serial.begin(115200);
}
void loop(){
    sensor1.measure_init();
    sensor2.measure_init();
    sensor3.measure_init();
    for(uint8_t i = 0; i < SAMPLE_PERIOD; i+=SAMPLE_STEP_PERIOD){
        sensor1.measure();
        sensor2.measure();
        sensor3.measure();
        delay(SAMPLE_STEP_PERIOD);
    }
    Serial.print(sensor1.get_value());
    Serial.print("/");
    //Serial.print(sensor2.get_value());
    Serial.print(0);
    Serial.print("/");
    //Serial.println(sensor3.get_value());
    Serial.println(0);
}