#include "led_manager.hpp"

LedManager::LedManager()
{
	prog = 0;
  last_press = millis();
	FastLED.addLeds<WS2812B, DATA_PIN,GRB>(leds, NUM_LEDS);
  max_lum = map(analogRead(MAX_LUM), 0, 1023, MIN_LUM, 255);
  wait = map(analogRead(SPEED), 0, 1023, 1, MAX_WAIT);
}

//Spiral
void LedManager::programme0(){
  static int hue = 0;
	for(int i=0; i<NUM_LEDS; i++)
	{
		int value = map((i+hue)%NUM_LEDS, 0, NUM_LEDS-1, max_lum, MIN_LUM);
		leds[i] = CHSV(hue, 255, value);
	}
	hue++;
}

//Fade
void LedManager::programme1()
{
  static long t = 0;
	int range = max_lum-MIN_LUM;

	long hue = floor(t/range);
	int value = cubicwave8(t)+ MIN_LUM;
	if(value > max_lum) 
		value = max_lum;
	fill_solid( &(leds[0]), NUM_LEDS, CHSV(hue, 255, value));
	t++;
}

//Rainbow
void LedManager::programme2()
{
  static long t = 0;
	for(int i=0; i<NUM_LEDS; i++)
	{
		int hue = map((i+t)%NUM_LEDS, 0, NUM_LEDS, 0, 255);
		leds[i] = CHSV(hue, 255, max_lum);
	}
	t++;
}

//double white
void LedManager::programme3()
{
  static int w1 = 0;
  static int w2 = NUM_LEDS;
  static int hue = 0;
	fill_solid( &(leds[0]), NUM_LEDS, CHSV(hue, 255, max_lum));
	leds[w1].setHSV(hue+128, 255, max_lum);
	leds[w2].setHSV(hue+128, 255, max_lum);
	w1 = (w1+1)%NUM_LEDS;
	w2 = (w2+(NUM_LEDS-1))%NUM_LEDS;
	hue ++;
}

void LedManager::programme4()
{
	static long t = 0;
	static int hue = 0;
	int i, j, l1, l2, range, nbL, value, nextHue;
	range = NUM_LEDS/4;
	nbL = t % range;
	nextHue = hue + range * 3;
	for(i = 0; i < 4; i++)
	{
		l1 = (hue + range * i) % NUM_LEDS;
		for(j = 0; j < range; j++)
		{
			l2 = (l1 + j) % NUM_LEDS;
			
			if(j < (nbL + 1))
			{
				value = map(j + 1, 0, nbL + 1, MIN_LUM, max_lum);
				leds[l2] = CHSV(nextHue, 255, value);
			}
			else 
			{
				value = map(j, 0, range, MIN_LUM, max_lum);
				leds[l2] = CHSV(hue, 255, value);
			}
		}
	}
	t++;
	if(t%range == 0)
	{
		hue = nextHue;
	}
}

void LedManager::programme5()
{
	static long t = 0;
	static int hue = 0;
	int i, j, ltmp, range, nbL, value, nextHue;
	range = NUM_LEDS/4;
	nbL = t % range;
	nextHue = hue + range * 3 + 1;
	fill_solid( &(leds[0]), NUM_LEDS, CHSV(hue, 255, MIN_LUM));
	for(i = 0; i < 4; i++)
	{
		ltmp = (hue + range * i) % NUM_LEDS;
		for(j = 0; j < range + 1; j++)
		{
			value = map(j, 0, range, max_lum, MIN_LUM);
			leds[ltmp + j] = CHSV(hue, 255, value);
		}
	}
	for(i = 0; i < 4; i++)
	{
		ltmp = (nextHue * i) % NUM_LEDS;
		for(j = 0; j < nbL + 1; j++)
		{
			value = map(j, 0, nbL, max_lum, MIN_LUM);
			leds[ltmp + j] = CHSV(nextHue, 255, value);
		}
	}
	if(!(t%(range)))
		hue = nextHue;
}

void LedManager::loop()
{
	switch(prog)
  {
    case 0: 
      programme0();
      break;
    case 1: 
      programme1();
      break;
    case 2: 
      programme2();
      break;
    case 3:
      programme3();
      break;
		case 4:
			programme4();
		break;
		case 5:
			programme5();
		break;
	}
  update_all();
}

void LedManager::update_all()
{
  max_lum = map(analogRead(MAX_LUM), 0, 1023, MIN_LUM, 255);
  wait = map(analogRead(SPEED), 0, 1023, 1, MAX_WAIT);
  FastLED.show();
  delay(wait);
}