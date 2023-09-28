#include <key/src/key.h>
// khai báo đối tượng phím nhấn
//@param _SWITCH_BUTTON_PIN : chân nhận tín hiệu nút nhấn
//@param _PULLUP: bật điện trở PULL_UP tại chân tín hiệu nút nhấn
SwitchKey::SwitchKey(uint8_t _SWITCH_BUTTON_PIN, bool _PULLUP)
{
    SWITCH_BUTTON_PIN = _SWITCH_BUTTON_PIN;
    isPULL_UP = _PULLUP;
}

SwitchKey::~SwitchKey()
{
}
void SwitchKey::initialize()
{
    isPULL_UP ? pinMode(SWITCH_BUTTON_PIN, INPUT_PULLUP) : pinMode(SWITCH_BUTTON_PIN, INPUT);
}
void SwitchKey::initialize(unsigned long _doubleClick_timeStamp_delta, unsigned long _hold_timeStamp_delta)
{
    pinMode(SWITCH_BUTTON_PIN, INPUT_PULLUP);
    doubleClick_timeStamp_delta = _doubleClick_timeStamp_delta;
    hold_timeStamp_delta = _hold_timeStamp_delta;
}
void SwitchKey::scan(unsigned long _timeStampNow)
{
    if (BUTTON_STATE == FREE_STATE)
    {
        if (digitalRead(SWITCH_BUTTON_PIN) == PRESSING && wasPressed == false)
        {
            pressed_timeStamp_Start = _timeStampNow;

            wasPressed = true;
        }
        else if (digitalRead(SWITCH_BUTTON_PIN) == PRESSING && wasPressed == true)
        {
            if (onHoldPressCallbackPointer)
            {
                if ((_timeStampNow - pressed_timeStamp_Start) >= hold_timeStamp_delta)
                {
                    BUTTON_STATE = HOLD_STATE;
                }
            }
        }
        else if (digitalRead(SWITCH_BUTTON_PIN) == NONE_PRESSING && wasPressed == true)
        {

            if ((_timeStampNow - pressed_timeStamp_Start) < hold_timeStamp_delta)
            {
                if (onDoubleClickCallbackPointer)
                {
                    BUTTON_STATE = FIRST_CLICK_STATE;
                    last_first_click_timeStamp = _timeStampNow;
                }
                else
                {
                    BUTTON_STATE = CLICK_STATE;
                    last_first_click_timeStamp = _timeStampNow;
                }
            }
            pressed_timeStamp_Start = millis();
            wasPressed = false;
        }
    }
    else
    {
        switch (BUTTON_STATE)
        {
        case FIRST_CLICK_STATE:
            if ((_timeStampNow - last_first_click_timeStamp) <= doubleClick_timeStamp_delta)
            {
                if (digitalRead(SWITCH_BUTTON_PIN) == PRESSING)
                {
                    BUTTON_STATE = DOUBLE_CLICK_STATE;
                }
            }
            else
            {
                BUTTON_STATE = CLICK_STATE;
            }
            break;
        case CLICK_STATE:
            if (digitalRead(SWITCH_BUTTON_PIN) == NONE_PRESSING)
            {
                (*onClickCallbackPointer)();
                BUTTON_STATE = FREE_STATE;
            }

            break;
        case DOUBLE_CLICK_STATE:
            if (digitalRead(SWITCH_BUTTON_PIN) == NONE_PRESSING)
            {
                (*onDoubleClickCallbackPointer)();
                BUTTON_STATE = FREE_STATE;
            }
            break;
        case HOLD_STATE: // sự kiện nhấn giữ
            (*onHoldPressCallbackPointer)();
            if (digitalRead(SWITCH_BUTTON_PIN) == NONE_PRESSING)
            {
                BUTTON_STATE = FREE_STATE;
            }
            break;
        default:
            break;
        }
    }
}