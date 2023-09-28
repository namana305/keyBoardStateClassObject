#include <ledRunning/src/ledRunning.h>

LedRunning::LedRunning()
{
}
LedRunning::~LedRunning(){
    
}
void LedRunning::initialize(int led_pin_to_set)
{
    if (led_pin_to_set != 13)
    {
        led_pin = led_pin_to_set;
    }
    else
    {
        led_pin = 13;
    }
    pinMode(led_pin, OUTPUT);
    timeStamp = millis();
}
void LedRunning::loop(unsigned long delay_time)
{
    if ((millis() - timeStamp) > delay_time)
    {
        if (led_sate == 0)
        {
            digitalWrite(led_pin, HIGH);
            led_sate = 1;
        }
        else
        {
            digitalWrite(led_pin, LOW);
            led_sate = 0;
        }
        timeStamp = millis();
    }
}