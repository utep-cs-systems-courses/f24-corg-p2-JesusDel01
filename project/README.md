Lab Project 2: Building a Toy
=============================

This code creates a little toy with 4 buttons that can be pressed.

How to run the code:
- Run "make load" in your terminal
- Wait for the program finishes loading into your MSP430
- Hit the reset button on the board

Button 1:
- Will alternatly turn on and off red and green every half second and play a different buzzer sound depending on the light that is on.

Button 2:
- Will turn on the green light and increase the buzzer tone. Once it reaches a certain tone the red light will turn on and decrease the buzzer tone.

Button 3:
- Will flash the green light as smaller intervals each time until it reaches 3 interrupts per second. Then the red light will start flashing at that same speed and will decrease each time until it reaches 80 intertupts per second.

Button 4:
- Will alternatly flash the red and green LED faster and faster until it reaches 5 interrupts per second. Then the Green and Red will flash at the same time and create a buzzer sound 5 times. 