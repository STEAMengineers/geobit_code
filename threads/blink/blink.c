#include "blink.h"
#include "pico/stdlib.h"
#include "tx_api.h"

#define BLINK_TICKS 20

void blink_thread_entry(ULONG thread_input) {
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (1) {
        gpio_put(LED_PIN, 1);
        tx_thread_sleep(BLINK_TICKS);
        gpio_put(LED_PIN, 0);
        tx_thread_sleep(BLINK_TICKS);
    }
}

void blink_thread_init(void) {
    static TX_THREAD blink_thread;
    static uint8_t blink_thread_stack[1024] __attribute__((aligned(8)));

    UINT status = tx_thread_create(&blink_thread, "Blink Thread", blink_thread_entry, 0,
        blink_thread_stack, sizeof(blink_thread_stack),
        1, 1, TX_NO_TIME_SLICE, TX_AUTO_START);
}