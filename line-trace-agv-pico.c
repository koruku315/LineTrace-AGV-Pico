#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

// モーター
#define AIN1 6
#define AIN2 7
#define BIN1 8
#define BIN2 9

// センサー（白=1, 黒(線)=0）
#define SENSOR_L 0
#define SENSOR_C 1
#define SENSOR_R 2

#define WRAP 255

#define LEFT_TRIM  1.00f
#define RIGHT_TRIM 1.00f

#define BASE_SPEED 170
#define KP 50.0f
#define KD 70.0f
#define KI 0.0f
#define MAX_SPEED 255
#define MIN_SPEED -60
static QueueHandle_t error_queue;

void pwm_init_pin(uint gpio) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(gpio);
    pwm_set_wrap(slice, WRAP);
    pwm_set_enabled(slice, true);
}

void set_pwm(uint gpio, uint16_t level) {
    pwm_set_gpio_level(gpio, level);
}

void left_motor(int speed) {
    int s = (int)(speed * LEFT_TRIM);
    if (s >= 0) { set_pwm(BIN1, 0);  set_pwm(BIN2, s); }
    else        { set_pwm(BIN1, -s); set_pwm(BIN2, 0); }
}
void right_motor(int speed) {
    int s = (int)(speed * RIGHT_TRIM);
    if (s >= 0) { set_pwm(AIN1, 0);  set_pwm(AIN2, s); }
    else        { set_pwm(AIN1, -s); set_pwm(AIN2, 0); }
}

void sensor_init(uint gpio) {
    gpio_init(gpio);
    gpio_set_dir(gpio, GPIO_IN);
}

int clamp(int v, int lo, int hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

void line_task(void *params) {
    sensor_init(SENSOR_L);
    sensor_init(SENSOR_C);
    sensor_init(SENSOR_R);

    int last_dir = 0;

    while (1) {
        int l = (gpio_get(SENSOR_L) == 0) ? 1 : 0;
        int c = (gpio_get(SENSOR_C) == 0) ? 1 : 0;
        int r = (gpio_get(SENSOR_R) == 0) ? 1 : 0;

        float error;
        int on_line = (l || c || r);

        if (!on_line) {
            error = (last_dir >= 0) ? 5.0f : -5.0f;
        } else {
            if      (l && !c && !r) error = -2.0f;
            else if (l &&  c && !r) error = -1.0f;
            else if (!l && c && !r) error =  0.0f;
            else if (!l && c &&  r) error =  1.0f;
            else if (!l && !c && r) error =  2.0f;
            else                    error =  0.0f;
            last_dir = (error > 0) ? 1 : (error < 0 ? -1 : last_dir);
        }

        xQueueOverwrite(error_queue, &error);
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}

void motor_task(void *params) {
    pwm_init_pin(AIN1); pwm_init_pin(AIN2);
    pwm_init_pin(BIN1); pwm_init_pin(BIN2);

    float last_error = 0.0f;
    float error = 0.0f;

    while (1) {
        if (xQueueReceive(error_queue, &error, portMAX_DELAY) == pdTRUE) {
            float p = error;
            float d = error - last_error;
            float correction = KP * p + KD * d;
            last_error = error;

            int left  = clamp((int)(BASE_SPEED + correction), MIN_SPEED, MAX_SPEED);
            int right = clamp((int)(BASE_SPEED - correction), MIN_SPEED, MAX_SPEED);

            left_motor(left);
            right_motor(right);
        }
    }
}

int main() {
    stdio_init_all();
    sleep_ms(2000);

    error_queue = xQueueCreate(1, sizeof(float));

    xTaskCreate(line_task,  "line",  256, NULL, 2, NULL);
    xTaskCreate(motor_task, "motor", 256, NULL, 3, NULL);

    vTaskStartScheduler();

    while (1) {}
}