/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 10  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work
*/
#include "timer.h"
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
unsigned char T,L;
enum BL_States { BL_SMStart, LedOff, LedOn } BL_State;
void TickFct_BlinkLed() 
{
	switch(BL_State)
	{
	case BL_SMStart: 
	BL_State = LedOff;
	break;
	case LedOff: 
	BL_State = LedOn;
	break;
	case LedOn: 
	BL_State = LedOff;
	break;
	}
	switch(BL_State)
	{
	case BL_SMStart: 
	break;
	case LedOff: 
	L = 0;
	break;
	case LedOn: 
	L = 0x08;
	break;
	}

}	
enum States { Start, Out} state;
void Combine(){
//unsigned char tmpB = 0x00;
	switch(state)
	{case Start: 
	state = Out;
	break;
	case Out:
	break;
	}
	switch(state)
	{case Start: 
	//state = Out;
	break;
	case Out:
	PORTB = T | L;
	}



}
enum TL_States { TL_SMStart, T0, T1, T2 } TL_State; 
void TickFct_ThreeLeds() {
   //... // Standard switch statements for SM
	switch(TL_State)
	{
	case TL_SMStart: 
	TL_State = T0;
	break;
	case T0: 
	TL_State = T1;
	break;
	case T1: 
	TL_State = T2;
	break;
	case T2:
	TL_State = T0;
	break;
	}
	switch(TL_State)
	{
	case TL_SMStart: 
	break;
	case T0: 
	T = 0x01;
	break;
	case T1: 
	T = 0x02;
	break;
	case T2:
	T = 0x04;
	break;

	}

}

int main(void) {
DDRB = 0xFF; PORTB = 0x00;
//   PORTB = 0; // Init outputs
unsigned long BL_elapsedTime = 1000;
   unsigned long TL_elapsedTime = 300;
   const unsigned long timerPeriod = 100; 
     
TimerSet(timerPeriod);
   TimerOn(); 
   BL_State = BL_SMStart;
   TL_State = TL_SMStart;
   state = Start; 
   while (1) {      
	if(BL_elapsedTime >= 1000)    
	{TickFct_BlinkLed();  
      BL_elapsedTime = 0;
	}
   if(TL_elapsedTime >= 300) 			  // Tick the BlinkLed synchSM
      {TickFct_ThreeLeds();
	TL_elapsedTime = 0;
	}
	 // if((TL_elapsedTime >= 300) && (BL_elapsedTime >= 1000))
	//{	
     // Combine();
//	TimerPeriod = 0;
//	}
      //PORTB = tmpB;   // Tick the ThreeLeds synchSM
      while (!TimerFlag){}   // Wait for timer period
      TimerFlag = 0;  
	Combine();       // Lower flag raised by timer
   	BL_elapsedTime += timerPeriod;
      TL_elapsedTime += timerPeriod;
	}
}
