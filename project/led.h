#ifndef led_included
#define led_included

#define LED_RED BIT6             // P1.0
#define LED_GREEN BIT0             // P1.6
#define LEDS (BIT0 | BIT6)

// functions for the LEDs
void init_leds(void);
void turn_on_green_led(void);
void turn_on_red_led(void);
void turn_on_green_assy(void);

#endif // included
