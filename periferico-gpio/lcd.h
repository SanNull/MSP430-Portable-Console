#include <msp430.h>
#include <stdint.h>
#include "./src/constantes.h"

void setUpLcd();
void LCD_setCursor(uint16_t x, uint16_t y);
void LCD_preencherRectangulo(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t cor);
void LCD_desenharPixel(uint16_t color);
void LCD_preencherTela(unsigned int color);
void LCD_desenharSprite(uint16_t *sprite, uint16_t x, uint16_t y, uint8_t tamanho);
