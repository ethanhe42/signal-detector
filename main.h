/*
 * main.h
 *
 *  Created on: Mar 24, 2015
 *      Author: Pomodori
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "TFT\TFT_Driver.h"

#define 	Square 				  BIT0
#define     Square_OUT            P2OUT
#define     Square_DIR            P2DIR
#define     Square_IN             P2IN
#define     Square_IE             P2IE
#define     Square_IES            P2IES
#define     Square_IFG            P2IFG
#define     Square_REN            P2REN


unsigned char calibrateUpdate = 0;

/* Using an 8-value moving average filter on sampled ADC values */
unsigned int tempMeasured[8];
unsigned char tempMeasuredPosition=0;
long tempAverage;

long tempCalibrated, tempDifference;

unsigned int counter=0;

void ConfigureAdcTempSensor(void)
{
	unsigned char i;
	/* Configure ADC Temp Sensor Channel */
	ADC10CTL1 = INCH_1 + ADC10DIV_3;         // Temp Sensor ADC10CLK/4
	ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON + ADC10IE+REF2_5V;
	__delay_cycles(1000);                     // Wait for ADC Ref to settle
	ADC10CTL0 |= ENC + ADC10SC;               // Sampling and conversion start
	__bis_SR_register(CPUOFF + GIE);          // LPM0 with interrupts enabled
	tempCalibrated = ADC10MEM;
	for (i=0; i < 8; i++)
		tempMeasured[i] = tempCalibrated;
	tempAverage = tempCalibrated;
}

void ConfigureTimerCount(void){
  TACTL=TASSEL_1+TACLR;
  CCTL0=CCIE;
  CCR0=200;  //  32768/200/2
  TACTL|=MC_1;
}

void ConfigureTimerCaptureFlow(void){

  Square_DIR &= ~Square;
  Square_OUT |= Square;
  Square_REN |= Square;
  Square_IES |= Square;
  Square_IFG &= ~Square;
  Square_IE |= Square;
//  TACTL=TASSEL_2+TACLR;
//  TACCTL1=CM_1+CAP+CCIE;
}

void InitializeClocks(void)
{

	BCSCTL1 |= DIVA_1;                        // ACLK/2
    BCSCTL3 |= LFXT1S_2;                      // ACLK = VLO

   BCSCTL1 = CALBC1_1MHZ;                    // Set range
   DCOCTL = CALDCO_1MHZ;
  BCSCTL2 &= ~(DIVS_0);                         // SMCLK = DCO / 8 = 1MHz
}



#endif /* MAIN_H_ */
