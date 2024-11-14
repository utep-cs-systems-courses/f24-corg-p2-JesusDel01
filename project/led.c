#include "led.h"
#include <msp430.h>

// Function to initialize the LED pins as outputs
void init_leds(void) {
    P1DIR |= LEDS; // Set P1.0 and P1.6 as outputs
}

// Function to turn on the green LED and turn off the red LED
void turn_on_green_led(void) {
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;
}

// Function to turn on the red LED and turn off the green LED
void turn_on_red_led(void) {
    P1OUT |= LED_RED;
    P1OUT &= ~LED_GREEN;
}
