#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <string.h>

// I2C defines
// use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9


#define SSD1306_ADDR  0x3C //(0, 7-bit) 011 11 0(SA0) 0(write)
#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64

// buffer for displaying 
uint8_t buffer[SSD1306_HEIGHT * SSD1306_WIDTH / 8 +1];

void init_ssd1306();
void cmd_ssd1306(uint8_t command);
void test_ssd1306() ;
void write_to_display_ssd1306();



void init_ssd1306() {
    // default i2c init
    i2c_init(I2C_PORT, 400*1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // default ssd1306 init sequence
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
    for (int i = 0; i < sizeof(init_sequence); i++) {
        printf("sequence: ");
        cmd_ssd1306(init_sequence[i]);
    }
    return;
}

void cmd_ssd1306(uint8_t command) {
    // 0 (Co: 0=followed by data byte) 0 (D/C#: 0=command, 1=data) 000000(default)
    uint8_t buff[2] = { 0x00, command };
    printf("%d \n", i2c_write_blocking(I2C_PORT, SSD1306_ADDR, buff, 2, false));
    return;
}

void test_ssd1306() {
    // set all to 1 (on)
    memset(buffer, 0xFF, sizeof(buffer));
    // set write to GDDRAM ( first command )
    buffer[0] = 0b01000000;
    write_to_display_ssd1306();
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


    while (1) {
        ;
    }

    // while (true) {
    //     printf("Hello, world!\n");
    //     sleep_ms(1000);
    // }
}
