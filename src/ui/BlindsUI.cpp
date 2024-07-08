#include <Arduino.h>
#include <lvgl.h>

#include "ui.h"

class BlindsUI {
public:
    BlindsUI(lv_obj_t *parent) {
        // Initialize the container
        blindsGroupContainer = lv_obj_create(parent);
        lv_obj_set_size(blindsGroupContainer, 222, 480);
        lv_obj_set_flex_flow(blindsGroupContainer, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_gap(blindsGroupContainer, 1, 0);
        set_common_styles(blindsGroupContainer);

        // Initialize label style
        lv_style_init(&label_style);
        lv_style_set_text_font(&label_style, &lv_font_montserrat_20); // Adjust font size as needed

        // Initialize button label style
        lv_style_init(&btn_label_style);
        lv_style_set_text_font(&btn_label_style, &lv_font_montserrat_22); // Adjust font size as needed
    }

    void addBlinds(const char *label_text, blinds_button_callback_t callback, void *user_data) {
        lv_obj_t *group = lv_obj_create(blindsGroupContainer);
        lv_obj_set_size(group, 222, LV_SIZE_CONTENT);
        lv_obj_set_flex_flow(group, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_style_pad_gap(group, 0, 0);
        set_common_styles(group);
        lv_obj_set_style_pad_bottom(group, 12, 0);

        // Label
        lv_obj_t *label = lv_label_create(group);
        lv_label_set_text(label, label_text);
        lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
        lv_obj_set_width(label, 222);  // Ensure the label takes the full width
        set_common_styles(label);
        lv_obj_set_style_pad_bottom(label, 6, 0);
        lv_obj_add_style(label, &label_style, 0); // Apply the larger font size

        // Button container
        lv_obj_t *btn_cont = lv_obj_create(group);
        lv_obj_set_size(btn_cont, 222, LV_SIZE_CONTENT);
        lv_obj_set_flex_flow(btn_cont, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_pad_gap(btn_cont, 10, 0);
        lv_obj_set_flex_align(btn_cont, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        set_common_styles(btn_cont);
        lv_obj_set_style_pad_bottom(btn_cont, 6, 0);

        // Buttons
        addButton(btn_cont, LV_SYMBOL_DOWN, DOWN, user_data);
        addButton(btn_cont, LV_SYMBOL_STOP, STOP, user_data);
        addButton(btn_cont, LV_SYMBOL_UP, UP, user_data);

        // Horizontal line
        lv_obj_t *line = lv_line_create(group);
        static lv_point_t line_points[] = {{0, 0}, {222, 0}}; // Adjust length as needed
        lv_line_set_points(line, line_points, 2);
        set_common_styles(line);
    }

private:
    lv_obj_t *blindsGroupContainer;
    lv_style_t label_style;
    lv_style_t btn_label_style;

    void set_common_styles(lv_obj_t *obj) {
        lv_obj_set_style_pad_left(obj, 0, 0);
        lv_obj_set_style_pad_right(obj, 0, 0);
        lv_obj_set_style_pad_top(obj, 0, 0);
        lv_obj_set_style_pad_bottom(obj, 0, 0);
        lv_obj_set_style_bg_opa(obj, LV_OPA_TRANSP, 0);  // Remove background
        lv_obj_set_style_border_width(obj, 0, 0);  // Remove border
        lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);  // Remove the scrollable flag
    }

    struct blinds_button_payload {
        blinds_button_t blinds_button;
        void *user_data;
        blinds_button_callback_t callback;
    };

    static void blinds_button_event_cb(lv_event_t *e) {
        lv_event_code_t code = lv_event_get_code(e);
        lv_obj_t *btn = lv_event_get_target(e);
        if (code == LV_EVENT_CLICKED) {
            blinds_button_payload *payload = (blinds_button_payload *)lv_event_get_user_data(e);
            payload->callback(payload->blinds_button, payload->user_data);
        }
    }

    void addButton(lv_obj_t *btn_cont, const char *t, blinds_button_t button, void *user_data) {
        blinds_button_payload *payload = (blinds_button_payload *)malloc(sizeof(blinds_button_payload));
        payload->blinds_button = button;
        payload->user_data = user_data;
        lv_obj_t *btn = lv_btn_create(btn_cont);
        lv_obj_set_size(btn, 60, 60);  // Resize the buttons to be 20% larger
        lv_obj_set_user_data(btn, payload);
        lv_obj_add_event_cb(btn, blinds_button_event_cb, LV_EVENT_CLICKED, payload);
        lv_obj_t *label = lv_label_create(btn);
        lv_label_set_text(label, t);
        lv_obj_add_style(label, &btn_label_style, 0); // Apply the larger font size
    }
};

void ui_init() {
    lv_obj_t *screen = lv_scr_act();
    BlindsUI blindsUI(screen);

    // Example usage
    blindsUI.addBlinds("Blinds 1", your_callback_function, your_user_data);
    blindsUI.addBlinds("Blinds 2", your_callback_function, your_user_data);
    // Add more groups as needed
}
