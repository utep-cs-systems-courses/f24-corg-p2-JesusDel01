#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"
#include "buttons.h"


void init_buttons(void){
  P2DIR &= ~(BIT0 | BIT1 | BIT2 | BIT3);       // Set P2.0 as input (S1 button)
  P2REN |= (BIT0 | BIT1 | BIT2 | BIT3);        // Enable pull-up/pull-down resistor on P2.0
  P2OUT |= (BIT0 | BIT1 | BIT2 | BIT3);// Configure pull-up resistor (button not pressed = high)

  // Enable interrupts for each button on Port 2
  P2IE |= (BIT0 | BIT1 | BIT2 | BIT3);
  P2IES |= (BIT0 | BIT1 | BIT2 | BIT3);  // Trigger on falling edge (button press)
  P2IFG &= ~(BIT0 | BIT1 | BIT2 | BIT3); // Clear interrupt flags for buttons
}

int main(void){ 
  configureClocks();           // Setup master oscillator, CPU & peripheral clocks
  init_leds();
  init_buttons();
  buzzer_init() ; 
  P1OUT &= ~LEDS;

  or_sr(0x18);

  return 0;
}
