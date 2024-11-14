#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"
#include "buttons.h"

//char check_buttons = 0;

void init_buttons(void){
  P2DIR &= ~(BIT0 | BIT1 | BIT2 | BIT3);       // Set P2.0 as input (S1 button)
  P2REN |= (BIT0 | BIT1 | BIT2 | BIT3);        // Enable pull-up/pull-down resistor on P2.0
  P2OUT |= (BIT0 | BIT1 | BIT2 | BIT3);        // Configure pull-up resistor (button not pressed = high)
}

int main(void){ 
  configureClocks();           // Setup master oscillator, CPU & peripheral clocks
  init_leds();
  init_buttons();
  buzzer_init() ; 
  P1OUT &= ~LEDS;

  _enable_interrupts();
  
  while(1){
    // if(check_buttons){
      if (!(P2IN & BIT0)) {
	button_1();  // Call the function when S1 is pressed
      }
      if(!(P2IN & BIT1)){
	button_2();
      }
      if(!(P2IN & BIT2)){
	button_3();
      }
      if(!(P2IN & BIT3)){
	button_4();
      }
      //or_sr(0x18);
      // }
  }
}

// WDT ISR to wake up the CPU periodically
//void __interrupt_vec(WDT_VECTOR) WDT(){
// check_buttons();
//}
