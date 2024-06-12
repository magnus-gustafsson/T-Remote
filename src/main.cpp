#include <Arduino.h>
#include <Arduino_GFX_Library.h>

#include "utilities.h"

#define GFX_BL BOARD_TFT_BL // default backlight pin, you may replace DF_GFX_BL to actual backlight pin

Arduino_DataBus *bus = new Arduino_ESP32SPI(BOARD_TFT_DC, BOARD_TFT_CS, BOARD_SPI_SCK, BOARD_SPI_MOSI, BOARD_SPI_MISO);

Arduino_GFX *gfx = new Arduino_ST7796(bus,
                                      BOARD_TFT_RST,
                                      0 /* rotation */,
                                      true /* IPS */,
                                      222,
                                      480, 49, 0);

void setup()
{
    gfx->begin();
    gfx->fillScreen(BLACK);

    pinMode(GFX_BL, OUTPUT);
    digitalWrite(GFX_BL, HIGH);

    // Define colors
    uint16_t textColor = WHITE;
    uint16_t shapeColor = WHITE;

    gfx->setTextSize(2);

    // Draw the first section
    gfx->setCursor(10, 30); // Adjust the Y position to match the font size
    gfx->setTextColor(textColor);
    gfx->println("Blinds Window");
    gfx->drawTriangle(50, 60, 70, 40, 90, 60, shapeColor);    // Upward triangle
    gfx->drawRect(100, 40, 20, 20, shapeColor);               // Square
    gfx->drawTriangle(120, 40, 140, 40, 130, 60, shapeColor); // Downward triangle
    gfx->drawLine(0, 80, 222, 80, shapeColor);                // Horizontal line

    // Draw the second section
    gfx->setCursor(10, 110); // Adjust the Y position to match the font size
    gfx->setTextColor(textColor);
    gfx->println("Blinds Door");
    gfx->drawTriangle(50, 140, 70, 120, 90, 140, shapeColor);    // Upward triangle
    gfx->drawRect(100, 120, 20, 20, shapeColor);                 // Square
    gfx->drawTriangle(120, 120, 140, 120, 130, 140, shapeColor); // Downward triangle
    gfx->drawLine(0, 160, 222, 160, shapeColor);                 // Horizontal line

    // Draw the third section
    gfx->setCursor(10, 190); // Adjust the Y position to match the font size
    gfx->setTextColor(textColor);
    gfx->println("Awning");
    gfx->drawTriangle(50, 220, 70, 200, 90, 220, shapeColor);    // Upward triangle
    gfx->drawRect(100, 200, 20, 20, shapeColor);                 // Square
    gfx->drawTriangle(120, 200, 140, 200, 130, 220, shapeColor); // Downward triangle
    gfx->drawLine(0, 240, 222, 240, shapeColor);                 // Horizontal line

    // Draw the fourth section
    gfx->setCursor(10, 270); // Adjust the Y position to match the font size
    gfx->setTextColor(textColor);
    gfx->println("Awning Dropdown");
    gfx->drawTriangle(50, 300, 70, 280, 90, 300, shapeColor);    // Upward triangle
    gfx->drawRect(100, 280, 20, 20, shapeColor);                 // Square
    gfx->drawTriangle(120, 280, 140, 280, 130, 300, shapeColor); // Downward triangle
    gfx->drawLine(0, 320, 222, 320, shapeColor);                 // Horizontal line
}

void loop()
{
    // Put your main code here, to run repeatedly:
}