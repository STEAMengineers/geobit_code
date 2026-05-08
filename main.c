#include <stdio.h>
#include "pico/stdlib.h"
#include "threads/blink/blink.h"
#include "tx_api.h"


void tx_application_define(void *first_unused_memory) {
    blink_thread_init();
}

int main()
{
    stdio_init_all();
    tx_kernel_enter();
}
