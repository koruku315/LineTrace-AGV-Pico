

#define SENSOR_L 0   // 左   GP0（列4）
#define SENSOR_C 1   // 中央 GP1（列5）
#define SENSOR_R 2   // 右   GP2（列7）

int main() {
    stdio_init_all();

    gpio_init(SENSOR_L);
    gpio_set_dir(SENSOR_L, GPIO_IN);
    gpio_init(SENSOR_C);
    gpio_set_dir(SENSOR_C, GPIO_IN);
    gpio_init(SENSOR_R);
    gpio_set_dir(SENSOR_R, GPIO_IN);

    while (true) {
        int l = gpio_get(SENSOR_L);
        int c = gpio_get(SENSOR_C);
        int r = gpio_get(SENSOR_R);

        printf("L=%d  C=%d  R=%d\n", l, c, r);
        sleep_ms(300);
    }
}
