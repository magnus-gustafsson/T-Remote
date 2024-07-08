#include <Arduino.h>
#include <Arduino_GFX_Library.h>

#include <lvgl.h>

#include "touch.h"
#include "utilities.h"
#include "ui/ui.h"

#define GFX_BL BOARD_TFT_BL // default backlight pin, you may replace DF_GFX_BL to actual backlight pin

/* More data bus class: https://github.com/moononournation/Arduino_GFX/wiki/Data-Bus-Class */
Arduino_DataBus *bus = new Arduino_ESP32SPI(BOARD_TFT_DC, BOARD_TFT_CS, BOARD_SPI_SCK, BOARD_SPI_MOSI, BOARD_SPI_MISO);

/* More display class: https://github.com/moononournation/Arduino_GFX/wiki/Display-Class */
Arduino_GFX *gfx = new Arduino_ST7796(bus,
                                      BOARD_TFT_RST,
                                      0 /* rotation */,
                                      true /* IPS */,
                                      222,
                                      480, 49, 0);

static uint32_t screenWidth;
static uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;
static lv_disp_drv_t disp_drv;
static unsigned long last_ms;

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP != 0)
    gfx->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#else
    gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#endif

    lv_disp_flush_ready(disp);
}

void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{

    if (touch_has_signal())
    {
        if (touch_touched())
        {
            data->state = LV_INDEV_STATE_PR;

            /*Set the coordinates*/
            data->point.x = touch_last_x;
            data->point.y = touch_last_y;

            Serial.print("Data x ");
            Serial.println(touch_last_x);

            Serial.print("Data y ");
            Serial.println(touch_last_y);
        }
        else if (touch_released())
        {
            data->state = LV_INDEV_STATE_REL;
        }
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;
    }
}

// Function to update the label with touch coordinates
// void update_touch_coordinates(int x, int y)
//{
//    static char buf[32];
//    snprintf(buf, sizeof(buf), "x: %d, y: %d", x, y);
//    lv_label_set_text(ui_Label1, buf);
//}


void btn_cb(blinds_button_t  pressed_button, void * user_data) {

}

void setup()
{

    Serial.begin(115200);
    delay(1);
    Serial.println("Entering setup");

    if (!gfx->begin())
    {
        Serial.println("gfx->begin() failed!");
    }

    gfx->fillScreen(BLACK);

#ifdef GFX_BL
    pinMode(GFX_BL, OUTPUT);
    digitalWrite(GFX_BL, HIGH);
#endif

    lv_init();

    screenWidth = gfx->width();
    screenHeight = gfx->height();

    disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * 40, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);

    lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * 40);

    /* Initialize the display */
    lv_disp_drv_init(&disp_drv);
    /* Change the following line to your display resolution */
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    /* Initialize the (dummy) input device driver */
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);

    touch_init(gfx->width(), gfx->height(), gfx->getRotation());

    ui_init();

    Serial.println("Setup done");

    create_blinds("Rullardin Fönster", btn_cb, (void *)"one");
    create_blinds("Rullardin Dörr", btn_cb, (void *)"one");
  create_blinds("Markis ", btn_cb, (void *)"one");
    create_blinds("Markis Dropp", btn_cb, (void *)"one");


}

void loop()
{
    Serial.println("In loop!");
    lv_timer_handler(); /* let the GUI do its work */
    delay(5);
}