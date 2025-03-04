#include "ui.h"
#include "time.h"
#include "esp_sntp.h"

static lv_timer_t * clock_timer;
static void update_clock(lv_timer_t * timer);
static void initialize_sntp(void);

void ui_Screen6_screen_init(void)
{
    ui_Screen6 = lv_obj_create(NULL);
    lv_obj_remove_flag(ui_Screen6, LV_OBJ_FLAG_SCROLLABLE);    /// Flags

    // Thay đổi từ Label_Home sang Label_Clock
    ui_Label_Clock = lv_label_create(ui_Screen6);
    lv_obj_set_width(ui_Label_Clock, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label_Clock, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_Label_Clock, -2);
    lv_obj_set_y(ui_Label_Clock, -1);
    lv_obj_set_align(ui_Label_Clock, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label_Clock, "Đang cập nhật...");  // Hiển thị khi đang khởi tạo
    lv_obj_set_style_text_font(ui_Label_Clock, &lv_font_montserrat_48, LV_PART_MAIN| LV_STATE_DEFAULT);

    // Khởi tạo SNTP để lấy thời gian từ internet
    initialize_sntp();

    // Tạo timer để cập nhật đồng hồ mỗi giây
    clock_timer = lv_timer_create(update_clock, 1000, NULL);

    lv_obj_add_event_cb(ui_Screen6, ui_event_Screen6, LV_EVENT_ALL, NULL);
}

// Khởi tạo SNTP để đồng bộ thời gian
static void initialize_sntp(void)
{
    esp_sntp_setoperatingmode(SNTP_OPMODE_POLL);
    esp_sntp_setservername(0, "pool.ntp.org");  // Server NTP toàn cầu
    esp_sntp_init();
    
    // Cài đặt múi giờ - ví dụ cho Việt Nam (UTC+7)
    setenv("TZ", "GMT-7", 1);
    tzset();
}

// Hàm cập nhật đồng hồ
static void update_clock(lv_timer_t * timer)
{
    time_t now;
    struct tm timeinfo;
    char time_str[32];
    
    time(&now);
    localtime_r(&now, &timeinfo);
    
    // Kiểm tra xem thời gian đã được đồng bộ chưa
    if (timeinfo.tm_year < (2023 - 1900)) {
        // Nếu chưa đồng bộ, hiển thị thông báo
        lv_label_set_text(ui_Label_Clock, "Wellcome...");
    } else {
        // Đã đồng bộ, hiển thị giờ:phút
        sprintf(time_str, "%02d:%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
        lv_label_set_text(ui_Label_Clock, time_str);
    }
}