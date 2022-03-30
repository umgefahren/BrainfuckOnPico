#include <stdio.h>
#include "pico/stdlib.h"
#include "parser.h"
#include "execute.h"

int main()
{
    stdio_init_all();

    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    unsigned char instructions[30000] = {0};

    unsigned short limit = parse(instructions);

    for (int i = 0; i < 30; i++) {
        printf("%i\n", i);
        sleep_ms(250);
    }

    while (true)
        execute(instructions, limit);

    puts("Hello, world!");

    return 0;
}
