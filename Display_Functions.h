#ifndef DISPLAY_FUNCTIONS_H_
#define DISPLAY_FUNCTIONS_H_

void HEX2RGB(String hex_value) {
	int number = (int) strtol( &hex_value[1], NULL, 16);
	color_array[0] = number >> 16;
	color_array[1] = number >> 8 & 0xFF;
	color_array[2] = number & 0xFF;
}

void TimeDisplay() {
	for (int i = 0; i <= NUM_LEDS; i++) {
		led_list[i] = 0;
	}
	led_list[7] = 1; led_list [15] = 1; led_list [23] = 1;
	int minute_unit = DateTime.minute % 10;
	int minute_tenth = DateTime.minute / 10;
	int hour_unit = DateTime.hour % 10;
	int hour_tenth = DateTime.hour / 10;
	//minute
	switch (minute_unit) {
	case 1: {
		led_list[3] = 1;
	}
	break;
	case 2: {
		led_list[6] = 1;
	}
	break;
	case 3: {
		led_list[1] = 1; led_list[4] = 1;
	}
	break;
	case 4: {
		led_list[2] = 1; led_list[5] = 1;
	}
	break;
	case 5: {
		led_list[2] = 1; led_list[3] = 1; led_list[5] = 1;
	}
	break;
	case 6: {
		led_list[0] = 1;
	}
	break;
	case 7: {
		led_list[0] = 1; led_list[3] = 1;
	}
	break;
	case 8: {
		led_list[0] = 1; led_list[6] = 1;
	}
	break;
	case 9: {
		led_list[0] = 1; led_list[3] = 1; led_list[6] = 1;
	}
	break;
	}
	switch (minute_tenth) {
	case 1: {
		led_list[11] = 1;
	}
	break;
	case 2: {
		led_list[14] = 1;
	}
	break;
	case 3: {
		led_list[9] = 1; led_list[12] = 1;
	}
	break;
	case 4: {
		led_list[10] = 1; led_list[13] = 1;
	}
	break;
	case 5: {
		led_list[10] = 1; led_list[11] = 1; led_list[13] = 1;
	}
	break;
	}
	//hour
	switch (hour_unit) {
	case 1: {
		led_list[19] = 1;
	}
	break;
	case 2: {
		led_list[16] = 1;
	}
	break;
	case 3: {
		led_list[18] = 1; led_list[21] = 1;
	}
	break;
	case 4: {
		led_list[17] = 1; led_list[20] = 1;
	}
	break;
	case 5: {
		led_list[17] = 1; led_list[19] = 1; led_list[20] = 1;
	}
	break;
	case 6: {
		led_list[22] = 1;
	}
	break;
	case 7: {
		led_list[19] = 1; led_list[22] = 1;
	}
	break;
	case 8: {
		led_list[16] = 1; led_list[22] = 1;
	}
	break;
	case 9: {
		led_list[16] = 1; led_list[19] = 1; led_list[22] = 1;
	}
	break;
	}
	switch (hour_tenth) {
	case 1: {
		led_list[27] = 1;
	}
	break;
	case 2: {
		led_list[24] = 1;
	}
	break;
	}
	for (int i = 0; i <= NUM_LEDS; i++) {
		if (led_list[i] == 1)  {
			leds[i] = solid_color;
		}
		else {
			leds[i] = CRGB(0,0,0);
		}
	}
}

void pulse_led() {
	int fadeAmount = 5;
	int brightness = 0;
	while (brightness < 255) {
		leds[15] = solid_color;
		leds[15].fadeLightBy(brightness);
		FastLED.show();
		FastLED.delay(5);
		brightness = brightness + fadeAmount;
		server.handleClient();
	}
	while (brightness > 0) {
		leds[15] = solid_color;
		leds[15].fadeLightBy(brightness);
		FastLED.show();
		FastLED.delay(5);
		brightness = brightness - fadeAmount;
		server.handleClient();
	}
}

void rainbow_led( uint8_t colorIndex) {
	for( int i = 0; i < NUM_LEDS; i++) {
		if (led_list[i] == 1) {
			leds[i] = ColorFromPalette( RainbowColors_p, colorIndex, 255, LINEARBLEND);
			colorIndex += 20;
		}
	}
}

//code from https://gist.github.com/kriegsman/99082f66a726bdff7776
const CRGB lightcolor(8,5,1);

void softtwinkles() {
	for( int i = 0; i < NUM_LEDS; i++) {
		if( !leds[i]) continue; // skip black pixels
		if( leds[i].r & 1) { // is red odd?
			leds[i] -= lightcolor; // darken if red is odd
		} else {
			leds[i] += lightcolor; // brighten if red is even
		}
	}
	// Randomly choose a pixel, and if it's black, 'bump' it up a little.
	// Since it will now have an EVEN red component, it will start getting
	// brighter over time.
	if( random8() < 40) {
		int j = random16(NUM_LEDS);
		if( !leds[j] ) leds[j] = lightcolor;
	}
}

void pride()
{
	static uint16_t sPseudotime = 0;
	static uint16_t sLastMillis = 0;
	static uint16_t sHue16 = 0;

	uint8_t sat8 = beatsin88( 87, 220, 250);
	uint8_t brightdepth = beatsin88( 341, 96, 224);
	uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
	uint8_t msmultiplier = beatsin88(147, 23, 60);

	uint16_t hue16 = sHue16;//gHue * 256;
	uint16_t hueinc16 = beatsin88(113, 1, 3000);

	uint16_t ms = millis();
	uint16_t deltams = ms - sLastMillis ;
	sLastMillis  = ms;
	sPseudotime += deltams * msmultiplier;
	sHue16 += deltams * beatsin88( 400, 5,9);
	uint16_t brightnesstheta16 = sPseudotime;

	for( uint16_t i = 0 ; i < NUM_LEDS; i++) {
		hue16 += hueinc16;
		uint8_t hue8 = hue16 / 256;

		brightnesstheta16  += brightnessthetainc16;
		uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

		uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
		uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
		bri8 += (255 - brightdepth);

		CRGB newcolor = CHSV( hue8, sat8, bri8);

		uint16_t pixelnumber = i;
		pixelnumber = (NUM_LEDS-1) - pixelnumber;

		nblend( leds[pixelnumber], newcolor, 64);
	}
}



#endif /* DISPLAY_FUNCTIONS_H_ */
