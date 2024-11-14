#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"
#include "buttons.h"

//flags to indicate which buttns use is active
static char bt_1 = 0;
static char bt_2 = 0;
static char bt_3 = 0;
static char bt_4 = 0;

void button_1(void) {
  bt_1 = 1;
  enableWDTInterrupts();
  _enable_interrupts();
}

void button_2(void) {
  bt_2 = 1;
  enableWDTInterrupts();
  _enable_interrupts();
}

void button_3(void) {
  bt_3 = 1;
  enableWDTInterrupts();
  _enable_interrupts();
}

void button_4(void) {
  bt_4 = 1;
  enableWDTInterrupts();
  _enable_interrupts();
}

// ISR for WDT 
void __interrupt_vec(WDT_VECTOR) WDT() {
  static char blink_count1 = 0; // counter for s1
  static char state = 0; // counter for s2
  static char state3 = 0; // counter for s3
  static char state4 = 0; // counter for s4
  static char interrupt_count1 = 0;
  static char interrupt_count2 = 0;
  static char interrupt_count3 = 0;
  static char interrupt_count4 = 0;
  static char light_delay = 80;
  static int pitch = 400;
  
  if (bt_1) interrupt_count1++;
  if (bt_2) interrupt_count2++;
  if (bt_3) interrupt_count3++;
  if (bt_4) interrupt_count4++;
  
  //code for button1
  if (bt_1 && interrupt_count1 >= 125) {  // 0.5-second delay
    interrupt_count1 = 0;

    if (blink_count1 < 10) {
      if (blink_count1 % 2 == 0) {
	//turn_on_green_led();
	turn_on_green_assy();
	buzzer_set_period(2000);  
      }
      else {
	turn_on_red_led();
	buzzer_set_period(1500);  
      }
      blink_count1++;
    }
    else{
      P1OUT &= ~LEDS;          // Turn off both LEDs
      buzzer_set_period(0);    // Stop the buzzer
      blink_count1 = 0;        // reset the count1 so that if it is called agian it is less than 10
      bt_1 = 0;
      IE1 &= ~WDTIE;
    }
  }

    //code for button 2
    if (bt_2 && interrupt_count2 >= 5){
      interrupt_count2 = 0;
      switch(state){
      case 0:
	if(pitch <= 3000){
	  turn_on_green_led();
	  buzzer_set_period(pitch);
	  pitch += 10;
	}else{
	  state = 1;
	}
	break;
      case 1:
	if (pitch >= 350){
	  turn_on_red_led();
	  buzzer_set_period(pitch);
	  pitch -= 10;
	}else{
	  state = 2;
	}
	break;
      case 2:
	P1OUT &= ~LED_RED;
	buzzer_set_period(0);  //stop the buzzer
	pitch = 300;           //reset pitch for the next use
	bt_2 = 0;
	state = 0;   //reset the Button 2 flag
	IE1 &= ~WDTIE;
	break;
      default:
	state = 0;
	break;
	
      }
    }

    // code for button 3
    if (bt_3 && interrupt_count3 >= light_delay){
      interrupt_count3 = 0;

      switch (state3) {
      case 0:  //blink green LED and decrease delay
	turn_on_green_led();
	buzzer_set_period(1800);
	state3 = 1;  //move to the next state
	break;
      case 1:  //turn off green LED and check delay threshold
	P1OUT &= ~LED_GREEN;
	buzzer_set_period(0);
	if (light_delay > 3) {
	  light_delay -= 3;  //decrease delay for faster blinking
	} else {
	  state3 = 2;
	  break;
	}
	state3 = 0;  //return to initial green state
	break;
      case 2:  // blink red LED and increase delay
	turn_on_red_led();
	buzzer_set_period(1800);
	state3 = 3; 
	break;
      case 3:  //turn off red LED and check delay threshold
	P1OUT &= ~LED_RED;
	buzzer_set_period(0);
	if (light_delay < 80) {
	  light_delay += 3;  
	} else {
	  state3 = 4;
	  break;
	}
	state3 = 2;  
	break;
      case 4:  
	light_delay = 80;
	buzzer_set_period(0);
	state3 = 0;  
	bt_3 = 0;  
	IE1 &= ~WDTIE;  
	break;
      default:
	state3 = 0;  
	break;
      }
    }

    //code for button 4
    if (bt_4 && interrupt_count4 >= light_delay) {  // 0.5-second delay                           
      interrupt_count4 = 0;

      switch(state4){
      case 0:
	turn_on_green_led();
        buzzer_set_period(1000);
        state4 = 1;  //move to the next state                                                     
        break;

      case 1:
	turn_on_red_led();
        buzzer_set_period(500);
        if (light_delay > 3) {
          light_delay -= 3;  //decrease delay for faster blinking
	  state4 = 0;
        } else {
          state4 = 2;
	  light_delay = 80;
        }
                                                      
        break;
      case 2:
	P1OUT |= LED_GREEN;
	P1OUT |= LED_RED;
	buzzer_set_period(2000);
	state4 = 3;
	break;

      case 3:
	P1OUT &= ~LED_GREEN;
        P1OUT &= ~LED_RED;
        buzzer_set_period(0);
	blink_count1++;
	if(blink_count1 < 6){
	  state4 = 2;
	}else{
	  state4 = 4;
	}
	break;

      case 4:
	light_delay = 80;
        buzzer_set_period(0);
        state4 = 0;
        bt_4 = 0;
	blink_count1 = 0;
        IE1 &= ~WDTIE;
        break;
      default:
	bt_4 = 0;
      }
    }
}

