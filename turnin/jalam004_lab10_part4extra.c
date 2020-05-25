/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
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
unsigned char T,L,S;
unsigned char N = 2;
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
enum N_States { N_start, inc, dec} N_state;
void Note() 
{
 unsigned char tmpA2 = ~PINA & 0x02;
 unsigned char tmpA1 = ~PINA & 0x01;

	switch(N_state)
	{
	case N_start: 
	if(tmpA1)
	{N++;
	N_state = inc;
	}	
        else if(tmpA2)
	{N_state = dec;}
	else if(N <= 1)
	{N = 1;}

	else{N--;}
	break;
	case inc:
	if(tmpA1)

{N_state = inc;}
else
{N_state = N_start; }
	break;
	case dec: 
	if(tmpA2)
	{N_state = dec;}
	else{N_state = N_start;}
	break;
	}
	switch(N_state)
	{
	case N_start: 
	break;
	case inc:
	break;
	case dec:
	break;
	}

}

enum S_States { start, Off, On } State;
void Speaker() 
{
 unsigned char tmpA = ~PINA & 0x04;

	switch(State)
	{
	case start: 
	State = Off;
	break;
	case Off:
	if((tmpA))	
	State = On;
	else{State = Off;}
	break;
	case On: 
	if((tmpA))
	State = Off;
	else{State = On;}
	break;
	}
	switch(State)
	{
	case start: 
	break;
	case Off: 
	S = 0;
	break;
	case On: 
	S = 0x10;
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
	PORTB = T | L | S;
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
DDRA = 0x00; PORTA = 0xFF;
//   PORTB = 0; // Init outputs
unsigned long BL_elapsedTime = 1000;
 unsigned long S_elapsedTime = N;
  unsigned long TL_elapsedTime = 300;
   //unsigned long N_elapsedTime = 1;
 const unsigned long timerPeriod = N; 
     //unsigned char tmpA = ~PINA & 0x01;
//Note();
TimerSet(timerPeriod);
   TimerOn(); 
   BL_State = BL_SMStart;
   TL_State = TL_SMStart;
   state = Start; 
   State = start;
   N_state = N_start;
   while (1) {      
	if(BL_elapsedTime >= 1000)    
	{TickFct_BlinkLed();  
      BL_elapsedTime = 0;
	}


 	if(S_elapsedTime >= N)    
	{
	Speaker(); // Combine();
	//Note();
      S_elapsedTime = 0;
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
  //Combine();    //PORTB = tmpB;   // Tick the ThreeLeds synchSM
      while (!TimerFlag){}   // Wait for timer period
      TimerFlag = 0;  
 Combine();
   	BL_elapsedTime += timerPeriod;
	S_elapsedTime += timerPeriod;
      TL_elapsedTime += timerPeriod;
	
}
}
