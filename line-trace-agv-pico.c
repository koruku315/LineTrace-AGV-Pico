#include <stdio.h>
#include "pico/stdlib.h"

#define SENSOR_DO_PIN 2   // GP2にセンサーのDOを接続

int main() {
    stdio_init_all();
    gpio_init(SENSOR_DO_PIN);
    gpio_set_dir(SENSOR_DO_PIN, GPIO_IN);

    while (true) {
        int value = gpio_get(SENSOR_DO_PIN);
        printf("Sensor DO = %d\n", value);
        sleep_ms(300);
    }
}
