#include <msp430.h>
#include <stdint.h>

void setUpLcd();
void LCD_setCursor(uint16_t x, uint16_t y);
void LCD_preencherRectangulo(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t cor);
void draw_pixel(uint16_t color);
