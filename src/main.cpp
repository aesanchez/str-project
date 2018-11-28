#include <Arduino.h>
#define INCLUDE_vTaskSuspend 1
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <Sensor.h>

#define PIN_SENSOR_1 3
#define PIN_SENSOR_2 2
#define SAMPLE_STEP_PERIOD 16 //in miliseconds. el minimo es de 16 por cosas de FREERTOS
#define SAMPLE_PERIOD 16*5

QueueHandle_t queue1;
QueueHandle_t queue2;

void task_sensor_1(void *pvParameters)
{
    Sensor sensor1(PIN_SENSOR_1);
    float value;
    int i;
    while (1)
    {   
        sensor1.measure_init();
        for (i = 0; i < SAMPLE_PERIOD; i += SAMPLE_STEP_PERIOD)
        {
            sensor1.measure_tick();
            vTaskDelay(SAMPLE_STEP_PERIOD/portTICK_PERIOD_MS);
        }
        value = sensor1.get_value();
        xQueueSend(queue1, &value, portMAX_DELAY);
    }
}
void task_sensor_2(void *pvParameters)
{
    float value;
    Sensor sensor2(PIN_SENSOR_2);
    int i;
    while (1)
    {   
        sensor2.measure_init();
        for (i = 0; i < SAMPLE_PERIOD; i += SAMPLE_STEP_PERIOD)
        {
            sensor2.measure_tick();
            vTaskDelay(SAMPLE_STEP_PERIOD/portTICK_PERIOD_MS);
        }
        value = sensor2.get_value();
        xQueueSend(queue2, &value, portMAX_DELAY);
    }
}

void task_sender(void *pvParameters)
{   
    float value1, value2;
    while(1){
        xQueueReceive(queue1, &value1, portMAX_DELAY);
        xQueueReceive(queue2, &value2, portMAX_DELAY);
        Serial.print(value1);
        Serial.print("/");
        Serial.println(value2);
    }
}

void setup()
{
    Serial.begin(115200);
    
    queue1 = xQueueCreate( 1, sizeof( float ) );
    queue2 = xQueueCreate( 1, sizeof( float ) );

    xTaskCreate(task_sensor_1, "task_name_1", 256, NULL, 1, NULL);
    xTaskCreate(task_sensor_2, "task_name_2", 256, NULL, 1, NULL);
    xTaskCreate(task_sender, "task_name_3", 256, NULL, 2, NULL);
}

void loop() {}