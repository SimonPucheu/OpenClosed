#include <Servo.h>
#include <PololuLedStrip.h>

#define ledCount 20

#define ledPin 3
#define servoPin 5
#define buttonPin 7
#define switchPin 9

Servo servo;
PololuLedStrip<ledPin> ledStrip;
rgb_color ledColors[ledCount];
rgb_color themeColors[2][3] =
{
  {rgb_color(255, 0, 0), rgb_color(100, 0, 100), rgb_color(0, 0, 255)},
  {rgb_color(0, 255, 0), rgb_color(0, 0, 255), rgb_color(0, 100, 100)}
};

int theme = 0;
int maxTheme = 3;
byte oldSwitchValue = NULL;

void setup()
{
  Serial.begin(9600);
  servo.attach(servoPin);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(switchPin, INPUT);
}

void loop()
{
  byte buttonValue = digitalRead(buttonPin);
  Serial.println(buttonValue);
  if (buttonValue == 0) {
    while (digitalRead(buttonPin) != 1);
    theme++;
    if (theme >= maxTheme) {
      theme = 0;
    }
    drawColor(oldSwitchValue);
  }
  byte switchValue = digitalRead(switchPin);
  if (switchValue != oldSwitchValue) {
    servo.write(switchValue * 180);
    drawColor(switchValue);
    oldSwitchValue = switchValue;
  }
  delay(50);
}

void drawColor(int value) {
  Serial.print("theme: "); Serial.println(theme);
  Serial.print("value: "); Serial.println(value);
  for (uint16_t i = 0; i < ledCount; i++) {
    ledColors[i] = themeColors[value][theme];
    ledStrip.write(ledColors, ledCount);
    delay(50);
  }
}
