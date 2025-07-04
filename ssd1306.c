/**
 * @file ssd1306.c
 * @author AS-096 
 * @brief Driver for SSD1306 displays on Raspberry Pi Pico
 * @version 0.1
 * @date 2025-07-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */



#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <string.h>
#include "ssd1306.h"

// buffer for displaying: first byte (byte 0) is command to
// set following bytes as data (for writing into GDDRAM),
// and the following bytes are the display bytes (1:on, 0:off)
uint8_t buffer[SSD1306_HEIGHT * SSD1306_WIDTH / 8 +1];


void init_ssd1306() {
    // default i2c init
    i2c_init(I2C_PORT, 400*1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // ssd1306 init sequence
    uint8_t init_sequence[] ={
        // Set MUX Ratio
        0xA8, 0x3F,
        // Set Display Offset 
        0xD3, 0x00,
        // Set Display Start Line
        0x40, 
        // Set Segment re-map 
        0xA0,
        // ! Set horizontal addressing mode 
        0x20,
        // Set COM Output Scan Direction
        0xC0, 
        // Set COM Pins hardware configuration
        0xDA, 0x02,
        // Set Contrast Control  
        0x81, 0x7F,
        // Disable Entire Display On 
        0xA4,
        // Set Normal Display 
        0xA6,
        // Set Osc Frequency 
        0xD5, 0x80,
        // Enable charge pump regulator
        0x8D, 0x14,
        // Display On 
        0xAF,
    };
    printf("ssd1306 init...");
    for (int i = 0; i < sizeof(init_sequence); i++) {
        cmd_ssd1306(init_sequence[i]);
    }
    // set write to GDDRAM 
    buffer[0] = 0b01000000;
    printf("ssd1306 init completed");
    return;
}

void cmd_ssd1306(uint8_t command) {
    // buffer for sending command
    // first byte:  set to send command [0 (Co: 0=followed by data byte) 0 (D/C#: 0=command, 1=data) 000000(default)]
    // second byte: command to send
    uint8_t buff[2] = { 0x00, command };
    // printf("%d \n", i2c_write_blocking(I2C_PORT, SSD1306_ADDR, buff, 2, false));
    i2c_write_blocking(I2C_PORT, SSD1306_ADDR, buff, 2, false);
    return;
}


void test_ssd1306() {
    // set all to 1 (on)
    memset(buffer+1, 0xFF, sizeof(buffer)-1);
    write_to_display_ssd1306();
    return;
}


void clear_ssd1306(bool updateDisplay) {
    memset(buffer+1, 0x00, sizeof(buffer)-1);
    // instantly update display
    if (updateDisplay) {
        write_to_display_ssd1306();
    }
    return;
}


void write_to_display_ssd1306() {
    i2c_write_blocking(I2C_PORT, SSD1306_ADDR, buffer, sizeof(buffer), false);
    return;
}



int main()
{
    stdio_init_all();
    sleep_ms(3000);


    init_ssd1306();
    test_ssd1306();
    sleep_ms(1000);
    clear_ssd1306(1);


    while (1) {
        ;
    }

    // while (true) {
    //     printf("Hello, world!\n");
    //     sleep_ms(1000);
    // }
}
