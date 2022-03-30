#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "pico/unique_id.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "parser.h"
#include "execute.h"

void print_temperature() {
    const float conversion_factor = 3.3f / (1 << 12);
    uint16_t result = adc_read();
    float voltage = result * conversion_factor;
    float temperature =  27.0 - (voltage - 0.706)/0.001721;
    printf("Temperature: %f°C\n", temperature);
}

int main()
{
    stdio_init_all();

    adc_init();

    adc_select_input(4);
    
    adc_set_temp_sensor_enabled(true);

    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    puts("Counting up from 0 to 10, waiting 250ms each time.");

    for (int i = 0; i < 10; i++)
    {
        printf("%i\n", i);
        sleep_ms(250);
    }

    pico_unique_board_id_t board_id;
    pico_get_unique_board_id(&board_id);

    puts("Brainfuck interpreter written by umgefahren (github.com/umgefahren).");
    printf("Running on Raspberry Pi Pico with id: %i-%i-%i-%i-%i-%i-%i-%i \n", board_id.id[0], board_id.id[1], board_id.id[2], board_id.id[3], board_id.id[4], board_id.id[5], board_id.id[6], board_id.id[7]);

    unsigned char instructions[30000] = {0};

    unsigned short limit = parse(instructions);

    while (true)
    {
        print_temperature();
        
        execute(instructions, limit);
        
        printf("Waiting 1s befor executing again.\n");
        sleep_ms(1000);
    }

    puts("Hello, world!");

    return 0;
}
