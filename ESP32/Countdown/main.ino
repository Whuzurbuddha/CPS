#include <cstdint>
constexpr std::uint8_t latchPin = 15;
constexpr std::uint8_t dataPin = 2;
constexpr std::uint8_t clockPin = 4;
constexpr std::uint8_t button = 14;
constexpr std::uint8_t green = 27;
constexpr std::uint8_t red = 26;
constexpr std::uint8_t yellow = 5;
constexpr std::uint8_t ton = 12;

std::uint8_t led_status = 0;
// status 0 => green
// status 1 => red
// status 2 => yellow
std::uint8_t counter = 0;
const byte datArray[] = 
{
        B11000000, // 0
        B11111001, // 1
        B10100100, // 2
        B10110000, // 3
        B10011001, // 4
        B10010010, // 5
        B10000010, // 6
        B11111000, // 7
        B10000000, // 8
        B10010000  // 9
};

void setup() 
{
    pinMode(clockPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(green, OUTPUT);
    pinMode(red, OUTPUT);
    pinMode(ton, OUTPUT);
    pinMode(yellow, OUTPUT);
    pinMode(button, INPUT_PULLUP);
    start();
}

void start()
{
  digitalWrite(red, HIGH);
  digitalWrite(green, HIGH);
  digitalWrite(yellow, HIGH);
  delay(800);
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
}

void loop() 
{
  delay(50); 
  if(digitalRead(button) == LOW)
  {
    switchLED();
    countdown();
    delay(50);
    led_status = 1;
    switchLED();
  }
}

void countdown()
{
  for(std::int32_t i = 9; i >= 0; --i)
  {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, datArray[i]);
    delay(1000);
    digitalWrite(latchPin, HIGH);
  }
  play_ton();
}

void play_ton()
{
  led_status = 2;
  switchLED();
  delay(5000);
}

void switchLED()
{
  if(led_status == 0)
  {
    led_status = 1;
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
  }else if(led_status == 1)
  {
    led_status = 0;
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
  }else
  {
    digitalWrite(red, LOW);
    digitalWrite(green, LOW);
    digitalWrite(yellow, HIGH);
  }
}
