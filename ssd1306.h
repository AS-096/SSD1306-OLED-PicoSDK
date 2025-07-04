#ifndef SSD1306_H
#define SSD1306_H


// I2C defines
// use I2C0 on GPIO8 (SDA) and GPIO9 (SCL).
#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9



/**
 * ~~~
 * 7-bit slave address - SSD1306 with SA0, in write mode
 * +----+----+----+----+----+----+-------+---------+
 * | B7 | B6 | B5 | B4 | B3 | B2 | B1    | B0      |
 * +----+----+----+----+----+----+-------+---------+
 * | -  |         Default        |  SA   | 0:Write |
 * |    |                        | (0/1) | 1:Read  |
 * +----+----+----+----+----+----+-------+---------+
 * | -  | 0  | 1  | 1  | 1  | 1  |   0   |    0    |
 * +----+----+----+----+----+----+-------+---------+
 * ~~~
 * 
 */
#define SSD1306_ADDR  0x3C 
// Set width of Display
#define SSD1306_WIDTH 128
// Set height of Display
#define SSD1306_HEIGHT 64



/**
 * @brief Initialize ssd1306
 * 
 */
void init_ssd1306();

/**
 * @brief Send command to SSD1306
 * 
 * @param command command to send SSD1306
 */
void cmd_ssd1306(uint8_t command);

/**
 * @brief Testing ssd1306 display by turning all pixels on
 * 
 */
void test_ssd1306() ;

/**
 * @brief Writing buffer data into display
 * 
 */
void write_to_display_ssd1306();

/**
 * @brief Reset display buffer to all 0 (off)
 * 
 * @param updateDisplay Update display after clearing if true
 */
void clear_ssd1306(bool updateDisplay);


#endif