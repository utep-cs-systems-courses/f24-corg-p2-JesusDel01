	.arch msp430g2553
	.p2align 1,0
	.text

	.global turn_on_green_assy
	.extern P1OUT

turn_on_green_assy:
	bis #1, &P1OUT     	; set Bit0 to turn on green
	and #~64, &P1OUT        ; set Bit 6 to turn off red 

	pop r0
