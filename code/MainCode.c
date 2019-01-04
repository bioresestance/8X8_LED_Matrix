//Aaron Bromma
/*
* This code controlls the  8x8 LED matrix .
* This code calls on both pre-made headers and code made by me.
*/

#include <p18cxxx.h>
#include <delays.h>
#include "Matrix.h"
#include "Games.h"

#pragma config FOSC = INTOSCIO_EC
#pragma config FCMEN = OFF, PWRT = ON
#pragma config WDT = OFF, MCLRE = OFF, PBADEN = OFF, LVP = OFF
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF, CPD = OFF


//**********************************************************************************************************

void main()
{
	
/////////////////////////////////Declarations//////////////////////////////////////////////////////////////////
	
unsigned int i=0, n=0, x=0;
	
/////////////////////////////////Main Code//////////////////////////////////////////////////////////////////

	Init();								//initilizes the pic

	ConnectFour();
	Swirl(1);

	while(1)							//infinate loop
	{
		
	}

}

//**********************************************************************************************************

