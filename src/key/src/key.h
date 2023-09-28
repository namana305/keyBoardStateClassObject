#ifndef _SWITCHKEY_H
#define _SWITCHKEY_H
#include <Arduino.h>

// algorithm

// định nghĩa các trạng thái chân tín hiệu nút nhấn và chính nó
#define PRESSING 0      // khi nút nhấn được nhấn tín hiệu đọc được là 0 (voltage) tương đương với mức LOW của arduino và logic 0
#define NONE_PRESSING 1 // khi nút nhấn được nhấn tín hiệu đọc được là giá trị điện áp =0.6*VCC =0.6*5~ 3 (voltage) tương đương với mức HIGH của arduino và logic 1

#define FREE_STATE 0         // Không nhấn
#define FIRST_CLICK_STATE 1  // nhấn lần đầu tiên
#define CLICK_STATE 2        // đúng là đã nhấn 1 lần
#define DOUBLE_CLICK_STATE 3 // nhấn double click
#define HOLD_STATE 4         // nhấn giữ
// khai báo lớp đối tượng phím nhấn
//@param _SWITCH_BUTTON_PIN : chân nhận tín hiệu nút nhấn
//@param _PULLUP: bật điện trở PULL_UP tại chân tín hiệu nút nhấn
class SwitchKey
{
private:
    unsigned long pressed_timeStamp_Start;
    bool wasPressed;
    unsigned long last_first_click_timeStamp;
    bool isPULL_UP;
    unsigned long doubleClick_timeStamp_delta = 100;
    unsigned long hold_timeStamp_delta = 2000;

public:
    uint8_t BUTTON_STATE;
    uint8_t SWITCH_BUTTON_PIN;
    SwitchKey(uint8_t _SWITCH_BUTTON_PIN, bool _PULLUP);
    ~SwitchKey();
    void initialize();
    void initialize(unsigned long _doubleClick_timeStamp_delta, unsigned long _hold_timeStamp_delta);
    void scan(unsigned long _timeStampNow);
    void (*onClickCallbackPointer)();
    void (*onDoubleClickCallbackPointer)();
    void (*onHoldPressCallbackPointer)();
};

#endif