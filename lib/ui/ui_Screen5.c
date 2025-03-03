// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 9.1.0
// Project name: Smart_

#include "ui.h"

void ui_Screen5_screen_init(void)
{
ui_Screen5 = lv_obj_create(NULL);
lv_obj_remove_flag( ui_Screen5, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Keyboard2 = lv_keyboard_create(ui_Screen5);
lv_keyboard_set_mode(ui_Keyboard2,LV_KEYBOARD_MODE_NUMBER);
lv_obj_set_width( ui_Keyboard2, 306);
lv_obj_set_height( ui_Keyboard2, 145);
lv_obj_set_x( ui_Keyboard2, 0 );
lv_obj_set_y( ui_Keyboard2, 41 );
lv_obj_set_align( ui_Keyboard2, LV_ALIGN_CENTER );

ui_TextArea3 = lv_textarea_create(ui_Screen5);
lv_obj_set_width( ui_TextArea3, 257);
lv_obj_set_height( ui_TextArea3, 39);
lv_obj_set_x( ui_TextArea3, -2 );
lv_obj_set_y( ui_TextArea3, -89 );
lv_obj_set_align( ui_TextArea3, LV_ALIGN_CENTER );
lv_textarea_set_placeholder_text(ui_TextArea3,"Password");


ui_Label11 = lv_label_create(ui_Screen5);
lv_obj_set_width( ui_Label11, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label11, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label11, -9 );
lv_obj_set_y( ui_Label11, -50 );
lv_obj_set_align( ui_Label11, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label11, "");
lv_obj_set_style_text_color(ui_Label11, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Label11, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_keyboard_set_textarea(ui_Keyboard2, ui_TextArea3);
lv_obj_add_event_cb(ui_Keyboard2, ui_event_Keyboard2, LV_EVENT_ALL, NULL);

lv_obj_add_event_cb(ui_Screen5, ui_event_Screen5, LV_EVENT_ALL, NULL);

}
