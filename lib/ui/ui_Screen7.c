// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 9.1.0
// Project name: Smart_

#include "ui.h"

void ui_Screen7_screen_init(void)
{
ui_Screen7 = lv_obj_create(NULL);
lv_obj_remove_flag( ui_Screen7, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label3 = lv_label_create(ui_Screen7);
lv_obj_set_width( ui_Label3, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label3, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label3, -7 );
lv_obj_set_y( ui_Label3, -2 );
lv_obj_set_align( ui_Label3, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label3,"OPEN");
lv_obj_set_style_text_opa(ui_Label3, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Label3, &lv_font_montserrat_48, LV_PART_MAIN| LV_STATE_DEFAULT);


}
