#include "Arduino.h"
#include <FastLED.h>
#ifndef LED_MANAGER_H
#define LED_MANAGER_H

#define NUM_LEDS 32
#define DATA_PIN 7


#define BUTTON 2

#define NB_PROG 6
#define DELAY_BUTTON 500

#define SPEED A0
#define MAX_WAIT 250

#define MAX_LUM A1
#define MIN_LUM 40
class LedManager
{
	
	public:
		volatile int prog;
		volatile long last_press;

		LedManager();
		void loop();
	
	protected :
		void programme0();
		void programme1();
		void programme2();
		void programme3();
		void programme4();
		void programme5();
		void update_all();
		int max_lum, wait;
		CRGB leds[NUM_LEDS];
};
#endif