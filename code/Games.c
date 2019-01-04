#include <delays.h>
#include <stdlib.h>
#include "p18cxxx.h"
#include "Matrix.h"
#include "Games.h"


void Swirl( unsigned int c)
{
	unsigned int i=0, n=0, x=0, m=0;

	for(m=0;m<c;m++)
	{	
		for(x=0;x<5;x++)
		{	
			for(i=1+n;i<9-n;i++)
			{
				SetRed(i,n+1);
				DrawMatrix(Wait);						
			}	
			for(i=2+n;i<9-n;i++)
			{
				SetRed(8-n,i);
				DrawMatrix(Wait);						
			}
			for(i=7-n;i>0+n;i--)
			{
				SetRed(i,8-n);
				DrawMatrix(Wait);						
			}	
			for(i=7-n;i>1+n;i--)
			{
				SetRed(n+1,i);
				DrawMatrix(Wait);						
			}		
			n++;
		}
		n=0;

		for(x=0;x<5;x++)
		{	
			for(i=1+n;i<9-n;i++)
			{
				SetGreen(i,n+1);
				DrawMatrix(Wait);						
			}	
			for(i=2+n;i<9-n;i++)
			{
				SetGreen(8-n,i);
				DrawMatrix(Wait);						
			}
			for(i=7-n;i>0+n;i--)
			{
				SetGreen(i,8-n);
				DrawMatrix(Wait);						
			}	
			for(i=7-n;i>1+n;i--)
			{
				SetGreen(n+1,i);
				DrawMatrix(Wait);						
			}		
			n++;
		}

		n=0;
		for(x=0;x<5;x++)
		{	
			for(i=1+n;i<9-n;i++)
			{
				SetBlue(i,n+1);
				DrawMatrix(Wait);						
			}	
			for(i=2+n;i<9-n;i++)
			{
				SetBlue(8-n,i);
				DrawMatrix(Wait);						
			}
			for(i=7-n;i>0+n;i--)
			{
				SetBlue(i,8-n);
				DrawMatrix(Wait);						
			}	
			for(i=7-n;i>1+n;i--)
			{
				SetBlue(n+1,i);
				DrawMatrix(Wait);						
			}			
			n++;
		}
		n=0;

		for(x=0;x<5;x++)
		{	
			for(i=1+n;i<9-n;i++)
			{
				SetPurple(i,n+1);
				DrawMatrix(Wait);						
			}		
			for(i=2+n;i<9-n;i++)
			{
				SetPurple(8-n,i);
				DrawMatrix(Wait);						
			}
			for(i=7-n;i>0+n;i--)
			{
				SetPurple(i,8-n);
				DrawMatrix(Wait);						
			}		
			for(i=7-n;i>1+n;i--)
			{
				SetPurple(n+1,i);
				DrawMatrix(Wait);						
			}			
			n++;
		}
		n=0;

		for(x=0;x<5;x++)
		{	
			for(i=1+n;i<9-n;i++)
			{
				SetCyan(i,n+1);
				DrawMatrix(Wait);						
			}		
			for(i=2+n;i<9-n;i++)
			{
				SetCyan(8-n,i);
				DrawMatrix(Wait);						
			}
			for(i=7-n;i>0+n;i--)
			{
				SetCyan(i,8-n);
				DrawMatrix(Wait);						
			}		
			for(i=7-n;i>1+n;i--)
			{
				SetCyan(n+1,i);
				DrawMatrix(Wait);						
			}		
			n++;
		}
		n=0;

		for(x=0;x<5;x++)
		{	
			for(i=1+n;i<9-n;i++)
			{
				SetOrange(i,n+1);
				DrawMatrix(Wait);						
			}
			for(i=2+n;i<9-n;i++)
			{
				SetOrange(8-n,i);
				DrawMatrix(Wait);						
			}
			for(i=7-n;i>0+n;i--)
			{
				SetOrange(i,8-n);
				DrawMatrix(Wait);						
			}		
			for(i=7-n;i>1+n;i--)
			{
				SetOrange(n+1,i);
				DrawMatrix(Wait);						
			}		
			n++;
		}
		n=0;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////


void ConnectFour(void)
{
	unsigned int i=0;
	unsigned int Row[8];
	unsigned char Flag=0, button=0, Turns=0;
	unsigned char Player=1;

	ClearAll();												//clears screen for new game

	for(i=1;i<9;i++)			
	{
		SetPurple(7,i);										//sets the boundries up
		SetPurple(8,i);
		Row[i-1]= 6; 										//initializes the Row variables
	}

	SetRed(1,Player);										//sets the initial position of pointer


	while(1)
	{
		DrawMatrix(1);										//continues to draw the picture			
		button=Buttons();									//checks to see if button was pushed

		if(button)											//if button is pushed...
		{
			while( Buttons() ) DrawMatrix(1);				//waits till button is released
			
			DrawMatrix(1);									//debounces the switch
		
			switch(button)									//do stuff acording to what button is pushed
			{
				case 'u': 		ClearOne(1,Player);			//clear previous position out
								if(Player==8)Player=1;		//rolls over player if at last position
								else Player++;				//move the player over one spot
								break;

				case 'l': 		if(Flag) 
								{
									for(i=2;i<Row[Player-1]+1;i++)	//adds a falling effect
									{
										SetOrange( i, Player);	// drops the player down
										ClearOne(i-1, Player);	//clears the previous position
										DrawMatrix(9);			//adds a delay to the drop
									}

								}
								else
								{
									for(i=2;i<Row[Player-1]+1;i++)	//add a falling effect
									{
										SetRed( i, Player);		// drops the player down
										ClearOne(i-1, Player);	//clears the previous position
										DrawMatrix(9);			//adds a deley to the drop
									}

								}

								if(Row[Player-1]>1) 		//checks to see if the player has reached the top		
								{
									Row[Player-1]--;		//moves the position in that row up one spot
									Flag ^=1;				//change players
									Turns++;
								}
								break;
	
				default	:		break;
			}
		}
		
		if(!Flag)	SetRed(1,Player);						//Draws the player
		if(Flag)	SetOrange(1,Player);

		if(Turns==40)	break;

	}

	

	

}