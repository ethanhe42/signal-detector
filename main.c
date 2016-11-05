#include  <msp430g2553.h>
#include "main.h"
#include "mas430g2553_it.h"

extern char line;
unsigned char s[5];
unsigned char letsprint=0;
unsigned int frequency=0;
void main(void)
{
  char calibrated=0;
  double T;

  unsigned char i;
  unsigned int PeriodCtr=0;
  unsigned char PeriodOnOff=0;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  InitializeClocks();

  TFT_Init();
  ConfigureAdcTempSensor();
  ConfigureTimerCount();
  ConfigureTimerCaptureFlow();
  _EINT();
  __enable_interrupt();                     // Enable interrupts.

  /* Main Application Loop */
  while(1)
  {
    if(letsprint){
		line=0;
		Println("voltage(mV):");
		T=tempAverage*2.5;

		s[0]=T/1000+'0';
		T-=(s[0]-'0')*1000;
		s[1]=T/100+'0';
		T-=(s[1]-'0')*100;
		s[2]=T/10+'0';
		T-=(s[2]-'0')*10;
		s[3]=T+'0';
		s[4]=0;
		Println(s);
		Println("frequency(Hz):");
		T=PeriodCtr*10;
		PeriodCtr=0;
		s[0]=T/1000+'0';
		T-=(s[0]-'0')*1000;
		s[1]=T/100+'0';
		T-=(s[1]-'0')*100;
		s[2]=T/10+'0';
		T-=(s[2]-'0')*10;
		s[3]=T+'0';
		s[4]=0;
		Println(s);
		Println("Square(Hz):");
		T=frequency/2.4;
		PeriodCtr=0;
		s[0]=T/10000+'0';
		T-=(s[0]-'0')*10000;
		s[1]=T/1000+'0';
		T-=(s[1]-'0')*1000;
		s[2]=T/100+'0';
		T-=(s[2]-'0')*100;
		s[3]=T/10+'0';
		T-=(s[3]-'0')*10;
		s[4]=T+'0';
		s[5]=0;
		Println(s);
		letsprint=0;
		frequency=0;
    }
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
    __bis_SR_register(CPUOFF + GIE);        // LPM0 with interrupts enabled

    tempMeasured[tempMeasuredPosition++] = ADC10MEM;
    if (tempMeasuredPosition == 8)
      tempMeasuredPosition = 0;

    if (tempMeasured[tempMeasuredPosition]<tempAverage&&PeriodOnOff)
    {
      PeriodOnOff=0;
      PeriodCtr++;
    }
    else if (tempMeasured[tempMeasuredPosition]>tempAverage&&PeriodOnOff==0)
    {
      PeriodOnOff=1;
    }
    tempAverage = 0;
    for (i = 0; i < 8; i++)
      tempAverage += tempMeasured[i];
    tempAverage >>= 3;                      // Divide by 8 to get average
    if(!calibrated){
  		calibrated=1;
  		tempCalibrated=tempAverage;
  	}
  }
}
