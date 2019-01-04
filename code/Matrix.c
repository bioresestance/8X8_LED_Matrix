#include "p18cxxx.h"
#include <delays.h>
#include "Matrix.h"
#include <stdlib.h>

unsigned char VramR[8];
unsigned char VramG[8];
unsigned char VramB[8];
unsigned char T_VramR[8];
unsigned char T_VramG[8];
unsigned char T_VramB[8];
unsigned char DataR[]= { 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff};//{0b10000001,0b00000000,0b00000000,0b11000001,0b00000000,0b00000000,0b11110001,0b00000000,0b00000000,0b11110001,0b00000000,0b00000000,0b10000111,0b00000000,0b00000000,0b10000011,0b00000000, 0b00000000,0b10111001,0b00000000,0b00000000,0b10000001,0b00000000,0b00000000,0b11100111,0b00000000,0b00000000,0b10011001,0b00000000,0b00000000,0b10111101,0b00000000,0b00000000,0b10000001,0b00000000,0b00000000,0b11000011,0b00000000,0b00000000,0b10010001,0b00000000,0b00000000,0b10111001,0b00000000,0b00000000,0b10000011,0b00000000,0b00000000,0b10000111,0b00000000,0b00000000,0b11110001,0b00000000,0b11111101,0b11111001,0b11110001,0b10000001,0b10000001,0b10110001,0b10110001,0b10110001};
unsigned char DataG[]= { 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff};//{0b00000000,0b10000001,0b11000001,0b00000000,0b11100001,0b00000000,0b00000000,0b11110001,0b00000000,0b00000000,0b11100001,0b00000000,0b00000000,0b10001111,0b00000000,0b00000000,0b10110001, 0b00000000,0b00000000,0b10111001,0b00000000,0b00000000,0b10000001,0b00000000,0b00000000,0b11000011,0b00000000,0b00000000,0b10011001,0b00000000,0b00000000,0b10011001,0b00000000,0b00000000,0b11000011,0b00000000,0b00000000,0b10000001,0b00000000,0b00000000,0b10110001,0b00000000,0b00000000,0b10011001,0b00000000,0b00000000,0b10000111,0b00000000,0b00000000,0b11000001,0b00000000,0b00000000,0b11111001,0b11111101,0b11111001,0b11110001,0b10000001,0b10000001,0b10110001,0b10110001,0b10110001};
unsigned char DataB[]= { 0xff, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00};//{0b00000000,0b10000001,0b11000001,0b00000000,0b00000000,0b11100001,0b00000000,0b00000000,0b11111001,0b00000000,0b00000000,0b11000011,0b00000000,0b00000000,0b10000111,0b00000000,0b00000000, 0b10111001,0b00000000,0b00000000,0b10010001,0b00000000,0b00000000,0b11000011,0b00000000,0b00000000,0b10000001,0b00000000,0b00000000,0b10111101,0b00000000,0b00000000,0b10011001,0b00000000,0b00000000,0b11100111,0b00000000,0b00000000,0b10000001,0b00000000,0b00000000,0b10111001,0b00000000,0b00000000,0b10000001,0b00000000,0b00000000,0b10001111,0b00000000,0b00000000,0b11100001,0b00000000,0b00000000,0b11111101,0b11111001,0b11110001,0b10000001,0b10000001,0b10110001,0b10110001,0b10110001};
unsigned char player=0b00010000;
unsigned char collide=0;
unsigned int Count=8;



//***************************************************************************************

void LoadGN(unsigned char data)
{
	GNE = 1;		//allow the green latch to get data
	DATA = data;	//puts the data to the latch
	GNE = 0;		//turns off the the latch
	DATA=0x00;
}

//***************************************************************************************

void LoadRD(unsigned char data)
{
	RDE = 1;		//allow the red latch to get data
	DATA = data;	//puts the data to the latch
	RDE = 0;		//turns off the the latch
	DATA=0x00;
}

//***************************************************************************************

void LoadBL(unsigned char data)
{
	BLE = 1;		//allow the green latch to get data
	DATA = data;	//puts the data to the latch
	BLE = 0;		//turns off the the latch
	DATA=0x00;
}

//***************************************************************************************

void LoadRow(unsigned char data)
{
	ROWE=1;
	DATA=data;
	ROWE=0;
	DATA=0x00;
}

//***************************************************************************************

void DrawMatrix(unsigned int n)
{

unsigned int loop,i;
unsigned int row=1;

	for(loop=0;loop<n;loop++)	//draws the matrix number of times specified by n
	{
		for(i=0;i<8;i++)		//draws all 8 lines out
		{
			LoadRow(row);		//chooses the row 
			LoadRD(VramR[i]);	//loads the colours into the latches
			LoadGN(VramG[i]);
			LoadBL(VramB[i]);
			OE=0;
			Delay10TCYx(1000);
			OE=1;
			LoadRow(row);		//clears out the latches
			LoadRD(0xff);
			LoadGN(0xff);
			LoadBL(0xff);
			OE=0;
			Delay10TCYx(50);
			OE=1;
			row *=2;
		}	
		row=1;
	}
}

//*************************************************************************************************************

void Init(void)
{
unsigned int i;
	
/////////////////////////////////General Set Up///////////////////////////////////////////////////////////////

TRISA = 0x00;
TRISB = 0x00;
TRISC = 0xFF;
OE=1;	
/////////////////////////////////sets up the internal oscilator///////////////////////////////////////////////

	OSCCONbits.IRCF2=1;					//refer to data sheet for what the bits do
	OSCCONbits.IRCF1=1;
	OSCCONbits.IRCF0=1;
	OSCCONbits.SCS0=0;
	OSCCONbits.SCS1=0;
	OSCCONbits.IRCF0=1;
	OSCCONbits.IRCF1=1;
	OSCCONbits.IRCF2=1;

///////////////////////////initilizes the Vrams//////////////////////////////////////////////////////////////

for(i=0;i<8;i++)
{
	VramR[i]=0xff;
	VramG[i]=0xff;
	VramB[i]=0xff;
	T_VramR[i]=0xff;
	T_VramG[i]=0xff;
	T_VramB[i]=0xff;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void ShiftUp(void)
{
	unsigned int i;

//////////////////////////////////////////////stores the Vram////////////////////////////////////////////////
	for(i=0;i<8;i++)
	{
		T_VramR[i]=VramR[i];
		T_VramG[i]=VramG[i];
		T_VramB[i]=VramB[i];
	}
/////////////////////////////////////////////////Shifts the Vram over one////////////////////////////////////	

	for(i=0;i<7;i++)
	{
		VramR[i]=T_VramR[i+1];	//shifts the data over
		VramG[i]=T_VramG[i+1];
		VramB[i]=T_VramB[i+1];
	}
		VramR[7]=DataR[Count];	//gets new byte to put in
		VramG[7]=DataG[Count];
		VramB[7]=DataB[Count];

	if(Count == 32){	Count=0;}
	else {Count++;	}
}

//***********************************************************************************************************

void ShiftDown(void)
{
	unsigned int i;
//////////////////////////////////////////////stores the Vram////////////////////////////////////////////////
	for(i=0;i<8;i++)
	{
		T_VramR[i]=VramR[i];
		T_VramG[i]=VramG[i];
		T_VramB[i]=VramB[i];
	}
//////////////////////////////////////////////Shifts the Vram over one////////////////////////////////////	

	for(i=7;i>0;i--)
	{
		VramR[i]=T_VramR[i-1];	//shifts the data over
		VramG[i]=T_VramG[i-1];
		VramB[i]=T_VramB[i-1];	
	}

		VramR[0]=DataR[Count];	//gets new byte to put in
		VramG[0]=DataG[Count];
		VramB[0]=DataB[Count];


	if(Count ==0)	Count=32;
	else Count--;	
}


//***********************************************************************************************************


char Buttons(void)
{
	unsigned char button=0;
	
		 if(UP) button='u';			//looks to see if any button has been pressed
	else if(DN) button='d';
	else if(LF) button='l';
	else if(RT) button='r';
	else if(UP) button='a';
	else if(UP) button='b';
	else if(UP) button='x';
	else if(UP) button='y';
				
	if(button != 0)	DrawMatrix(1);	//debounce if button is pushed

	return button;					//return the button pressed
}

//***********************************************************************************************************

void Collision(void)
{
unsigned int i=0;

	if(collide)
	{
		for(i=0;i<7;i++)
		{
			VramR[i]= 0x0f;
			VramG[i]= 0x0f;
			VramB[i]= 0x0f;			
		}

		while(1)	DrawMatrix(1);
	}
	else	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
void GenerateTerrain(void)
{
long unsigned int i=0, data=0;;


	i= rand()/128;
		

	if( i>=0 && i <= 50) 		data= 0b01111110;
	else if( i>50 && i <= 100)	data= 0b01100110;
	else if( i>100 && i <= 150)	data= 0b01110010;
	else if( i>150 && i <= 200)	data= 0b01100010;
	else if( i>200 )			data= 0b00011100;

	data=i;

	DataG[Count]= data;
	
	data=0;
				
}	

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void SetRed( unsigned char Row, unsigned char Col)
{
	unsigned char Pointer=0b00000001;
	ClearOne(Row,Col);
	Pointer = Pointer << (Col-1);		//chooses the collum to turn on
	Pointer ^= 0xFF;					//XOR's it to allow light to turn on
	VramR[Row-1] &= Pointer;			//AND's the ram to put data in it
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void SetBlue( unsigned char Row, unsigned char Col)
{
	unsigned char Pointer=0b00000001;
	ClearOne(Row,Col);
	Pointer = Pointer << (Col-1);		//chooses the collum to turn on
	Pointer ^= 0xFF;					//XOR's it to allow light to turn on
	VramB[Row-1] &= Pointer;			//AND's the ram to put data in it
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void SetGreen( unsigned char Row, unsigned char Col)
{
	unsigned char Pointer=0b00000001;
	ClearOne(Row,Col);
	Pointer = Pointer << (Col-1);		//chooses the collum to turn on
	Pointer ^= 0xFF;					//XOR's it to allow light to turn on
	VramG[Row-1] &= Pointer;			//AND's the ram to put data in it
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void SetWhite( unsigned char Row, unsigned char Col)
{
	unsigned char Pointer=0b00000001;
	ClearOne(Row,Col);
	Pointer = Pointer << (Col-1);		//chooses the collum to turn on
	Pointer ^= 0xFF;					//XOR's it to allow light to turn on
	VramR[Row-1] &= Pointer;			//AND's the ram to put data in it
	VramG[Row-1] &= Pointer;			//AND's the ram to put data in it
	VramB[Row-1] &= Pointer;			//AND's the ram to put data in it
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void SetPurple( unsigned char Row, unsigned char Col)
{
	unsigned char Pointer=0b00000001;
	ClearOne(Row,Col);
	Pointer = Pointer << (Col-1);		//chooses the collum to turn on
	Pointer ^= 0xFF;					//XOR's it to allow light to turn on
	VramR[Row-1] &= Pointer;			//AND's the ram to put data in it
	VramB[Row-1] &= Pointer;			//AND's the ram to put data in it
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void SetOrange( unsigned char Row, unsigned char Col)
{
	unsigned char Pointer=0b00000001;
	ClearOne(Row,Col);
	Pointer = Pointer << (Col-1);		//chooses the collum to turn on
	Pointer ^= 0xFF;					//XOR's it to allow light to turn on
	VramR[Row-1] &= Pointer;			//AND's the ram to put data in it
	VramG[Row-1] &= Pointer;			//AND's the ram to put data in it
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void SetCyan( unsigned char Row, unsigned char Col)
{
	unsigned char Pointer=0b00000001;
	ClearOne(Row,Col);
	Pointer = Pointer << (Col-1);		//chooses the collum to turn on
	Pointer ^= 0xFF;					//XOR's it to allow light to turn on
	VramG[Row-1] &= Pointer;			//AND's the ram to put data in it
	VramB[Row-1] &= Pointer;			//AND's the ram to put data in it
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void ClearAll( void )
{
	unsigned int i=0;
	
	for(i=0;i<8;i++)
	{
		VramR[i]=0xFF;
		VramG[i]=0xFF;
		VramB[i]=0xFF;
	}
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void ClearOne( unsigned char Row, unsigned char Col)
{
	unsigned char Pointer=0b00000001;
	
	Pointer = Pointer << (Col-1);		//chooses the collum to turn off
	VramR[Row-1] |= Pointer;			//AND's the ram to put data in it
	VramG[Row-1] |= Pointer;			//AND's the ram to put data in it
	VramB[Row-1] |= Pointer;			//AND's the ram to put data in it

}

