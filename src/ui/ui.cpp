#include <Arduino.h>
#include "ui.h"


lv_obj_t *label;
int count = 0;

static void btn_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        count++;

        char buf[32];
        snprintf(buf, sizeof(buf), "Pressed #: %d", count);
        lv_label_set_text(label, buf);
    }
}

void ui_init(void)
{

    label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "Initial Text");
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 20);

    
    lv_obj_t *btn = lv_btn_create(lv_scr_act());
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 20);
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *btn_label = lv_label_create(btn);
    lv_label_set_text(btn_label, "Press me");
    lv_obj_center(btn_label);

}



enum  roller_button_t
{
    UP, DOWN, STOP
} ;


typedef void (*roller_button_callback_t)(roller_button_t  pressed_button, void * user_data);


struct roller_button_payload
{
    roller_button_t roller_button;
    void * user_data;
    roller_button_callback_t callback;
} ;


static void btn_event_cb(lv_event_t * e)
{ 
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) 
    {
        roller_button_payload *payload = (roller_button_payload*)lv_event_get_user_data(e);
        payload->callback(payload->roller_button, payload->user_data);
    }
    

}


void create_roller(const char * label_text, roller_button_callback_t callback, void * user_data) 
{
    auto roller_label = lv_label_create(lv_scr_act());
    lv_label_set_text(roller_label, label_text);
    lv_obj_align(roller_label, LV_ALIGN_TOP_MID, 0, 20);

    roller_button_payload up_button_payload;
    up_button_payload.roller_button = UP;
    up_button_payload.user_data = user_data;

    lv_obj_t *btn = lv_btn_create(lv_scr_act());
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 20);
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_CLICKED, &up_button_payload);

    lv_obj_t *btn_label = lv_label_create(btn);
    lv_label_set_text(btn_label, "Press me");
    lv_obj_center(btn_label);
    
    
}

void button_pressed_callback(roller_button_t pressed_button, void * user_data)
{

}
