/*
 * mas430g2553_it.h
 *
 *  Created on: Mar 24, 2015
 *      Author: Pomodori
 */

#ifndef MAS430G2553_IT_H_
#define MAS430G2553_IT_H_

extern unsigned int counter;
extern unsigned char letsprint;
extern unsigned int frequency;

#pragma vector = TIMER0_A0_VECTOR;
 __interrupt void Timer_A(void){
		counter++;
		if(counter>=82){
			counter=0;
			letsprint=1;
		}
 }

#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR(void)
{
	  Square_IFG = 0;
//	  Square_IE &= ~Square;            /* Debounce */

	  WDTCTL = WDT_ADLY_250;
	  IFG1 &= ~WDTIFG;                 /* clear interrupt flag */
	  IE1 |= WDTIE;
	  frequency++;
}

#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void)
{
    IE1 &= ~WDTIE;                   /* disable interrupt */
    IFG1 &= ~WDTIFG;                 /* clear interrupt flag */
    WDTCTL = WDTPW + WDTHOLD;        /* put WDT back in hold state */
    Square_IE |= Square;             /* Debouncing complete */
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Return to active mode
}




#endif /* MAS430G2553_IT_H_ */
