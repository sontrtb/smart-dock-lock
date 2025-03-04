// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 9.1.0
// Project name: Smart_

#include "ui.h"
#include "ui_helpers.h"
#include "wifi_save.h"
#include "../../src/mqtt_handler.h"

static lv_timer_t *wifi_connect_timer = NULL;
static lv_timer_t *check_credentials_timer = NULL;

lv_timer_t *back_home_timer = NULL;

///////////////////// VARIABLES ////////////////////

// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
lv_obj_t *ui_Screen1;
lv_obj_t *ui_Label1;
void ui_event_Button1(lv_event_t *e);
lv_obj_t *ui_Button1;
lv_obj_t *ui_Label2;
// CUSTOM VARIABLES

// SCREEN: ui_Screen2
void ui_Screen2_screen_init(void);
lv_obj_t *ui_Screen2;
lv_obj_t *ui_Header1;
lv_obj_t *ui_Label8;
void ui_event_Button4(lv_event_t *e);
lv_obj_t *ui_Button4;
lv_obj_t *ui_Label9;
lv_obj_t *ui_Container2;
void ui_event_Panel2(lv_event_t *e, char *net);
lv_obj_t *ui_Panel2;
lv_obj_t *ui_Label5;
lv_obj_t *ui_Button_Refetch_Wifi;
// CUSTOM VARIABLES

// SCREEN: ui_Screen3
void ui_Screen3_screen_init(void);
lv_obj_t *ui_Screen3;
lv_obj_t *ui_Header2;
lv_obj_t *ui_Label6;
void ui_event_Button3(lv_event_t *e);
lv_obj_t *ui_Button3;
lv_obj_t *ui_Label7;
lv_obj_t *ui_TextArea1;
void ui_event_Keyboard1(lv_event_t *e);
lv_obj_t *ui_Keyboard1;
// CUSTOM VARIABLES

// SCREEN: ui_Screen4
void ui_Screen4_screen_init(void);
lv_obj_t *ui_Screen4;
lv_obj_t *ui_Spinner1;
lv_obj_t *ui_Label10;
void ui_event_Screen4(lv_event_t *e); // CUSTOM VARIABLES

// SCREEN: ui_Screen5
void ui_Screen5_screen_init(void);
lv_obj_t *ui_Screen5;
void ui_event_Keyboard2(lv_event_t *e);
void ui_event_Screen5(lv_event_t *e);
lv_obj_t *ui_Keyboard2;
lv_obj_t *ui_TextArea3;
lv_obj_t *ui_Label11;
// CUSTOM VARIABLES

// SCREEN: ui_Screen6
void ui_Screen6_screen_init(void);
lv_obj_t *ui_Screen6;
lv_obj_t *ui_Label_Clock;
void ui_event_Screen6(lv_event_t *e);
// CUSTOM VARIABLES

// SCREEN: ui_Screen7
void ui_Screen7_screen_init(void);
lv_obj_t *ui_Screen7;
lv_obj_t *ui_Label3;
// CUSTOM VARIABLES

// SCREEN: ui_Screen0
void ui_Screen0_screen_init(void);
lv_obj_t *ui_Screen0;
lv_obj_t *ui_Label4;
// CUSTOM VARIABLES

// EVENTS
lv_obj_t *ui____initial_actions0;

// IMAGES AND IMAGE SETS

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
#error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_Button1(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_screen_change(&ui_Screen2, LV_SCR_LOAD_ANIM_MOVE_LEFT, 300, 0, &ui_Screen2_screen_init);
    }
}

void ui_event_Button4(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_screen_change(&ui_Screen1, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 300, 0, &ui_Screen1_screen_init);
    }
}

void ui_event_Panel2(lv_event_t *e, char *net)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        onSelectWifiItem(net);
    }
    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_screen_change(&ui_Screen3, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_Screen3_screen_init);
    }
}

void ui_event_Button3(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_screen_change(&ui_Screen2, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 300, 0, &ui_Screen2_screen_init);
    }
}

void ui_event_Keyboard1(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_READY)
    {
        const char *password = lv_textarea_get_text(ui_TextArea1);
        onSelectWifiPassword(password);
    }
    if (event_code == LV_EVENT_READY)
    {
        _ui_screen_change(&ui_Screen4, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_Screen4_screen_init);
    }
}

void ui_event_Keyboard2(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        lv_timer_reset(back_home_timer);
    }

    if (event_code == LV_EVENT_READY)
    {

        const char *code = lv_textarea_get_text(ui_TextArea3);

        if (strlen(code) == 0)
        {
            return;
        };

        lv_label_set_text(ui_Label11, "");
        sendOTP(code);
        lv_textarea_set_text(ui_TextArea3, "");
    }
}

void ui_event_Screen6(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_screen_change(&ui_Screen5, LV_SCR_LOAD_ANIM_FADE_ON, 300, 0, &ui_Screen5_screen_init);
    }
}

void start_wifi_connection(lv_timer_t *timer)
{
    connectToWiFi();
}

void ui_event_Screen4(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_SCREEN_LOADED)
    {
        // Create a timer that will start the connection after the UI has rendered
        wifi_connect_timer = lv_timer_create(start_wifi_connection, 500, NULL);
        lv_timer_set_repeat_count(wifi_connect_timer, 1); // Run only once
    }
}

void back_home(lv_timer_t *timer)
{
    if (back_home_timer != NULL)
    {
        lv_timer_del(back_home_timer);
        back_home_timer = NULL;
    }

    lv_textarea_set_text(ui_TextArea3, "");
    _ui_screen_change(&ui_Screen6, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 300, 0, &ui_Screen6_screen_init);
}

void ui_event_Screen5(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_SCREEN_LOADED)
    {
        back_home_timer = lv_timer_create(back_home, 10000, NULL);
        lv_timer_set_repeat_count(back_home_timer, 1);
    }
}

// New function to check credentials and load appropriate screen
void check_credentials_and_load_screen(lv_timer_t *timer)
{
    WiFiSave wifiSave;
    String wifi_name = wifiSave.getWiFiName();
    String wifi_password = wifiSave.getWiFiPassword();

    if (!wifi_name.isEmpty() && !wifi_password.isEmpty())
    {
        _ui_screen_change(&ui_Screen4, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_Screen4_screen_init);
    }
    else
    {
        _ui_screen_change(&ui_Screen1, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_Screen1_screen_init);
    }
}

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    lv_disp_t *dispp = lv_display_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);

    ui_Screen0_screen_init();
    ui_Screen1_screen_init();
    ui_Screen2_screen_init();
    ui_Screen3_screen_init();
    ui_Screen4_screen_init();
    ui_Screen5_screen_init();
    ui_Screen6_screen_init();
    ui_Screen7_screen_init();

    ui____initial_actions0 = lv_obj_create(NULL);

    // Always start with Screen1
    lv_disp_load_scr(ui_Screen0);

    // Create a timer to check credentials after UI is fully loaded
    check_credentials_timer = lv_timer_create(check_credentials_and_load_screen, 500, NULL);
    lv_timer_set_repeat_count(check_credentials_timer, 1); // Run only once
}