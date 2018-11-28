#include <Arduino.h>
#define INCLUDE_vTaskSuspend 1
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <Sensor.h>

#define PIN_SENSOR_1 2
#define PIN_SENSOR_2 3
#define PIN_LED_R 6
#define PIN_LED_Y 5
#define PIN_LED_G 4
#define PIN_RELAY 7
#define SAMPLE_STEP_PERIOD 16 //in miliseconds. el minimo es de 16 por cosas de FREERTOS
#define SAMPLE_PERIOD 16 * 3

QueueHandle_t queue1;
QueueHandle_t queue2;
float value1, value2;
QueueHandle_t leds_sensor_1;

void task_sensor_1(void *pvParameters)
{
    Sensor sensor(PIN_SENSOR_1);
    float value;
    int i;
    while (1)
    {
        sensor.measure_init();
        for (i = 0; i < SAMPLE_PERIOD; i += SAMPLE_STEP_PERIOD)
        {
            sensor.measure_tick();
            //fix feo
            delay(8);
            sensor.measure_tick();
            vTaskDelay(SAMPLE_STEP_PERIOD / portTICK_PERIOD_MS);
        }
        value = sensor.get_value();
        xQueueSend(queue1, &value, portMAX_DELAY);
    }
}
void task_sensor_2(void *pvParameters)
{
    float value;
    Sensor sensor(PIN_SENSOR_2);
    int i;
    while (1)
    {
        sensor.measure_init();
        for (i = 0; i < SAMPLE_PERIOD; i += SAMPLE_STEP_PERIOD)
        {
            sensor.measure_tick();
            //fix feo
            delay(8);
            sensor.measure_tick();
            vTaskDelay(SAMPLE_STEP_PERIOD / portTICK_PERIOD_MS);
        }
        value = sensor.get_value();
        xQueueSend(queue2, &value, portMAX_DELAY);
    }
}

void task_sender(void *pvParameters)
{
    while (1)
    {
        xQueueReceive(queue1, &value1, portMAX_DELAY);
        xQueueReceive(queue2, &value2, portMAX_DELAY);
        // Serial.print(value1);
        // Serial.print("/");
        // Serial.println(value2);
    }
}
void task_IDLE(void *pvParameters)
{
    pinMode(PIN_LED_R, OUTPUT);
    pinMode(PIN_LED_Y, OUTPUT);
    pinMode(PIN_LED_G, OUTPUT);
    pinMode(PIN_RELAY, OUTPUT);
    unsigned long StartTime = 0;
    while (1)
    {
        if (Serial.available() > 0)
        {
            // read the incoming byte:
            Serial.println(Serial.read());
        }
        if (value1 > 0.05)
            digitalWrite(PIN_LED_G, LOW);
        else
            digitalWrite(PIN_LED_G, HIGH);

        if (value1 > 0.33)
            digitalWrite(PIN_LED_Y, LOW);
        else
            digitalWrite(PIN_LED_Y, HIGH);

        if (value1 > 0.66){
            digitalWrite(PIN_LED_R, LOW);
            if(StartTime == 0)//not measuring
                StartTime = millis();
            else{//was measuring
                Serial.println((millis() - StartTime));
                if((millis() - StartTime) > 5000){
                    //5 seconds over the threshold
                    digitalWrite(PIN_RELAY, LOW);                   
                }
            }
        }else{
            digitalWrite(PIN_LED_R, HIGH);
            StartTime = 0;
            digitalWrite(PIN_RELAY, HIGH);
        }
    }
}
void setup()
{
    Serial.begin(115200);

    queue1 = xQueueCreate(1, sizeof(float));
    queue2 = xQueueCreate(1, sizeof(float));
    if(queue1 == NULL)
        Serial.println("Error al crear cola 1");
    if(queue2 == NULL)
        Serial.println("Error al crear cola 2");
        
    //xTaskCreate(task_IDLE, "task_IDLE", 128, NULL, 0, NULL);
    xTaskCreate(task_sensor_1, "task_sensor_1", 256, NULL, 1, NULL);
    xTaskCreate(task_sensor_2, "task_sensor_2", 256, NULL, 1, NULL);
    xTaskCreate(task_sender, "task_sender", 128, NULL, 2, NULL);
}

void loop() {}