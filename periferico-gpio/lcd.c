#include "lcd.h"
#include "spi.h"

//Pinos P3
#define CS BIT1
#define RESET BIT7
#define DC BIT5

#define MAX_W 240
#define MAX_H 320

static void enviarComando(uint8_t comando);
static void enviarParametro(uint8_t parametro);

void setXCursor(uint16_t x);
void setYCursor(uint16_t y);
//Code Snippet from 
// @vilaca: https://gist.github.com/vilaca/1d07fa7ba9afcfe5ad74
static void initLcd(){
	P3OUT |= RESET;
	__delay_cycles(10000);
	P3OUT &= ~RESET;
	__delay_cycles(10000);
	P3OUT |= RESET;
	__delay_cycles(100000);

	enviarComando(0xCB);	// POWER CONTROL A
	enviarParametro(0x39);	// 1. (default)
	enviarParametro(0x2C);	// 2. (default)
	enviarParametro(0x00);	// 3. (default)
	enviarParametro(0x34);	// 4. (Vcore Controll: 1.55V, default)
	enviarParametro(0x02);	// 5. (DDVDH: 5.8V, default)

	enviarComando(0xCF);	// POWER CONTROL B
	enviarParametro(0x00);	// 1. (default)
	enviarParametro(0xC1);	// 2. (PC&EQ operation for power saving enabled), 0x81 def.
	enviarParametro(0x30);	// 3. (default)

	enviarComando(0xE8);	// DRIVER TIMING CONTROL A
	enviarParametro(0x85);	// 1. (gate driver non-overlap timing control), 0x84 def.
	enviarParametro(0x00);	// 2. (EQ timing control), 0x11 def.
	enviarParametro(0x78);	// 3. (pre-charge timing control), 0x7A def.

	enviarComando(0xEA);	// DRIVER TIMING CONTROL A
	enviarParametro(0x00);	// 1. (gate driver timing control), 0x66 def.
	enviarParametro(0x00);	// 2. (default)

	enviarComando(0xED);	// POWER ON SEQUENCE CONTROL
	enviarParametro(0x64);	// 1. (soft start control), 0x55 def.
	enviarParametro(0x03);	// 2. (power on sequence control), 0x01 def.
	enviarParametro(0x12);	// 3. (power on sequence control), 0x23 def.
	enviarParametro(0x81);	// 4. (DDVDH enhance mode(only for 8 external capacitors)), enabled, 0x01 def.

	enviarComando(0xF7);	// PUMP RATION CONTROL
	enviarParametro(0x20);	// 1. (ratio control)

	enviarComando(0xC0); 	// POWER CONTROL 1
	enviarParametro(0x23); 	// 1. (set the GVDD level, 4.6V), 0x21 def.

	enviarComando(0xC1); 	// POWER CONTROL 2
	enviarParametro(0x10); 	// 1. (sets the factor used in the step-up circuits) default

	enviarComando(0xC5); 	// VCOM CONTROL 1
	enviarParametro(0x3e); 	// 1. (VCOMH voltage = 5.85V), 0x31 def.
	enviarParametro(0x28);	// 2. (VCOML voltage = -1.50V), 0x3C def.

	enviarComando(0xC7); 	// VCOM CONTROL 2
	enviarParametro(0x86); 	// 1. (VCOM offset voltage), 0xC0 def.

	enviarComando(0x36); 	// MEMORY ACCESS CONTROL / Orientation
	enviarParametro(0x88); 	// 1. ( ), 0x00 def.

	enviarComando(0x3A);	// COLMOD: PIXEL FORMAT SET
	enviarParametro(0x55);	// 1. (sets the pixel format for the RGB image data used by the interface, 16bits/pixel)

	enviarComando(0xB1);	// FRAME RATE CONTROL (IN NORMAL MODE / FULL COLORS)
	enviarParametro(0x00);	// 1. (division ratio for internal clocks when Normal mode), default
	enviarParametro(0x1b);	// 2. (frame frequency, 79Hz), 0x1B def. (70Hz)

	enviarComando(0xB6); 	// DISPLAY FUNCTION CONTROL
	enviarParametro(0x08);	// 1. (), 0x0A def.
	enviarParametro(0x82);	// 2. (default)
	enviarParametro(0x27);	// 3. (default)

	enviarComando(0xF2); 	// 3GAMMA CONTROL
	enviarParametro(0x00);	// 1. (disabled), 0x02 def.

	enviarComando(0x26);	// GAMMA SET
	enviarParametro(0x01);	// 1. (default)

	enviarComando(0xE0); 	// POSITIVE GAMMA CORRECTION
	enviarParametro(0x0F);	// 1.
	enviarParametro(0x31);	// 2.
	enviarParametro(0x2B);	// 3.
	enviarParametro(0x0C);	// 4.
	enviarParametro(0x0E);	// 5.
	enviarParametro(0x08);	// 6.
	enviarParametro(0x4E);	// 7.
	enviarParametro(0xF1);	// 8.
	enviarParametro(0x37);	// 9.
	enviarParametro(0x07);	// 10.
	enviarParametro(0x10);	// 11.
	enviarParametro(0x03);	// 12.
	enviarParametro(0x0E);	// 13.
	enviarParametro(0x09);	// 14.
	enviarParametro(0x00);	// 15.

	enviarComando(0xE1); 	// NEGATIVE GAMMA CORRECTION
	enviarParametro(0x00);	// 1.
	enviarParametro(0x0E);	// 2.
	enviarParametro(0x14);	// 3.
	enviarParametro(0x03);	// 4.
	enviarParametro(0x11);	// 5.
	enviarParametro(0x07);	// 6.
	enviarParametro(0x31);	// 7.
	enviarParametro(0xC1);	// 8.
	enviarParametro(0x48);	// 9.
	enviarParametro(0x08);	// 10.
	enviarParametro(0x0F);	// 11.
	enviarParametro(0x0C);	// 12.
	enviarParametro(0x31);	// 13.
	enviarParametro(0x36);	// 14.
	enviarParametro(0x0F);	// 15.

//Sleep Out
	enviarComando(0x11);
	__delay_cycles(120000);

	enviarComando(0x2C);

	enviarComando(0x29);
	enviarComando(0x2C);
}

void setUpLcd(){
    setUpSpi();
    P3DIR |= CS + RESET + DC;   
    P3OUT |= RESET + DC;
    P3OUT &= ~CS;
    initLcd();
    LCD_preencherTela(0x00);
}


static void enviarComando(uint8_t comando){
	while  (SPI_estaOcupado());
    P3OUT &= ~DC;
	SPI_enviar(comando);
}

static void enviarParametro(uint8_t parametro){
	while  (SPI_estaOcupado());
    P3OUT |= DC;
	SPI_enviar(parametro);
}

void LCD_setCursor(uint16_t x, uint16_t y){
	setXCursor(x);
	setYCursor(y);
	//Write to memory
	enviarComando(0x2C);	
}

void setXCursor(uint16_t x) {
	if (x >= MAX_W) {
		return;
	}
	//Set Column Cursor 
	enviarComando(0x2A);
	enviarParametro(x >> 8); //MSB Start Column
	enviarParametro(x & 0xff); // LSB
	//Write to memory
	enviarComando(0x2C);	
}

void setYCursor(uint16_t y){
	if (y >= MAX_H){
		return;
	}
	//Set Page Cursor
	enviarComando(0x2B);
	enviarParametro(y >> 8); //MSB Start Page
	enviarParametro(y & 0xff);  // LSB
	//Write to memory
	enviarComando(0x2C);	
}


void LCD_desenharPixel(uint16_t color) {
	enviarParametro( color >> 8);
	enviarParametro( color & 0xFF);
}

void LCD_preencherRectangulo(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t cor){
	if (x >= MAX_W || x + w >= MAX_W || y >= MAX_H || y + h >= MAX_H){
		return;
	}
	LCD_setCursor(x, y);
	uint16_t i, j;
	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			LCD_desenharPixel(cor);
		}
		LCD_setCursor(x, ++y);
	}
}

void LCD_desenharSprite(uint16_t *sprite, uint16_t x, uint16_t y, uint8_t tamanho) {
	if (x >= MAX_W || x + tamanho >= MAX_W || y >= MAX_H || y + tamanho >= MAX_H){
		return;
	}	
	LCD_setCursor(x, y);
	uint16_t totalPixels = tamanho * tamanho;
	uint16_t i = 0;
	uint8_t pixelColuna = 0; //Variável para saber quando incrementar linha
	while (totalPixels-- > 0) {
		if (pixelColuna == tamanho){
			LCD_setCursor(x, ++y);
			pixelColuna = 0;
		}
		// if (sprite[i] == COR_MASCARA){
		// 	++i;
		// 	++pixelColuna;
		// 	LCD_setCursor(pixelColuna + x, y);
		// 	continue;
		// }
		LCD_desenharPixel(sprite[i++]);
		pixelColuna++;
	}
}

void LCD_preencherTela(unsigned int color)
{
	uint16_t altura = MAX_H;
	uint16_t largura = MAX_W;
	enviarComando(0x2A);
	enviarParametro( 0);
	enviarParametro( 0);
	enviarParametro( (MAX_W-1) >> 8);
	enviarParametro( (MAX_W-1) & 0xFF);
	enviarComando(0x2C);

	enviarComando(0x2B);
	enviarParametro( 0);
	enviarParametro( 0);
	enviarParametro( (MAX_H-1) >> 8);
	enviarParametro( (MAX_H-1) & 0xFF);
	enviarComando(0x2C);

	while ( altura--)
	{
		while (largura--) {
			LCD_desenharPixel(color);
		}
		largura = MAX_W;
	}
}