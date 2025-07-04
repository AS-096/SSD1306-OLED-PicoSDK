# SSD1306 OLED PicoSDK software driver



# Updating display
To update the display, simply change the data stored in `buffer`, then call `write_to_display_ssd1306()`.
`write_to_display_ssd1306()` will write everything in `buffer` to SSD1306.

### `buffer`
The buffer stores the data for the information to be displayed.
| Byte | [0]                            | [1]          | [2]          | ... | [(SSD1306_HEIGHT * SSD1306_WIDTH)/8] |
|------|--------------------------------|--------------|--------------|-----|--------------------------------------|
| Data | Command to write GDDRAM (0x40) | display data | display data | ... | graphics data                        |

Because we will have to tell the controller we want to write data, byte 0 will be the control byte.
It should, therefore, always be 0x40 and never change.

#### Display data
Following byte 0, there are `(SSD1306_HEIGHT * SSD1306_WIDTH) / 8` bytes. e.g. if the screen is `128 * 64` resolution, then there will be `128 * 64 / 8 = 1024` bytes
Each bit of these bytes represents on/off state of each pixel of the display.
Since the horizontal addressing mode of SSD1306 is less intuitive (at least for me), this driver uses vertical addressing mode.

#### Vertical addressing mode
The data is ordered 8 pixels as a group (byte), from top of first column to the bottom, then continue with the next column, till the last column. 
However, for each byte, the order from top to bottom within the 8 pixels (bits) is from LSB to MSB.
e.g.: to light up pixel on `col 0` `row 0`, set `buffer[1] = 0b00000001`