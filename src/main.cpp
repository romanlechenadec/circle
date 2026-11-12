#include "led_manager.hpp"

LedManager leds;

static void buttonRoutine()
{
  long t = millis();
  if(t - leds.last_press > DELAY_BUTTON)
  {
    leds.prog = (leds.prog +1) % NB_PROG;
    leds.last_press = t;
  }
}

void setup()
{
  // put your setup code here, to run once:
  
  pinMode(BUTTON,INPUT_PULLUP);
  pinMode(SPEED,INPUT);
  pinMode(MAX_LUM,INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON),buttonRoutine, FALLING);

  
  Serial.begin(9600);

}
void loop()
{
  // put your main code here, to run repeatedly:
  leds.loop();
}
