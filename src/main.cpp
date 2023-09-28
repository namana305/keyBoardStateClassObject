#include <Arduino.h>
#include <ledRunning/src/ledRunning.h>
#include <key/src/key.h>
// định nghĩa các chân điều khiển led
#define LED_GREEN 3
#define LED_BLUE 4
#define LED_RED 5

LedRunning ledRunMCU;
SwitchKey key1(2, true);
SwitchKey key2(7, true);
unsigned long timeLine_now;
void _key1ClickCallBack();
void _key1DoubleClickCallBack();
void _key1HoldPressCallBack();

void _key2ClickCallBack();
void _key2DoubleClickCallBack();
void _key2HoldPressCallBack();

void _key1ClickCallBack()
{
  Serial.println("key 1 click");
  Serial.println(key1.BUTTON_STATE);
};
void _key1DoubleClickCallBack()
{
  Serial.println("key 1  double click");
  Serial.println(key1.BUTTON_STATE);
};
void _key1HoldPressCallBack()
{
  Serial.println("key 1  hold press");
  Serial.println(key1.BUTTON_STATE);
};

void _key2ClickCallBack()
{
  Serial.println("key 2 click");
  Serial.println(key2.BUTTON_STATE);
};
void _key2DoubleClickCallBack()
{
  Serial.println("key 2 double click");
  Serial.println(key2.BUTTON_STATE);
};
void _key2HoldPressCallBack()
{
  Serial.println("key 2 hold press");
  Serial.println(key2.BUTTON_STATE);
};
void setup()
{
  Serial.begin(115200); // bật Serial để debug khi có lỗi
  // cấu hình các đèn
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  // pinMode(SWITCH_BUTTON_PIN, INPUT_PULLUP);
  // cấu hình cho đối tượng LedRunning
  ledRunMCU.initialize(LED_BUILTIN);
  key1.initialize(100, 1000);
  key1.onClickCallbackPointer = &_key1ClickCallBack;
  key1.onDoubleClickCallbackPointer = &_key1DoubleClickCallBack;
  key1.onHoldPressCallbackPointer = &_key1HoldPressCallBack;

  key2.initialize(100, 1000);
  key2.onClickCallbackPointer = &_key2ClickCallBack;
  key2.onDoubleClickCallbackPointer = &_key2DoubleClickCallBack;
  key2.onHoldPressCallbackPointer = &_key2HoldPressCallBack;
  // key1.onDoubleClickCallbackPointer = &_clickCallBack;
  Serial.println("notification: System started if system is running,led bulit-in will be flash every 200 milliseconds");
}

void loop()
{

  ledRunMCU.loop(1000);    // yên cầu đối tượng LedRunning nhấp nháy mỗi 1 giây để biêt rằng mcu không bị treo
  timeLine_now = millis(); // lấy giá trị thời gian hiện tại 1 lần cho 1 lần loop để tránh gọi hàm millis() quá nhiều làm yếu hiệu năng mcu
  key1.scan(timeLine_now);
  key2.scan(timeLine_now);
}
