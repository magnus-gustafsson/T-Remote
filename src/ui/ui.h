#pragma once


enum  blinds_button_t
{
    UP, DOWN, STOP
};


typedef void (*blinds_button_callback_t)(blinds_button_t  pressed_button, void * user_data);

void create_blinds(const char * label_text, blinds_button_callback_t callback, void * user_data);


void ui_init(void);

