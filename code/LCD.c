#include <p18cxxx.h>
#include"LCD.h"
#include<delays.h>

unsigned char BusyLCD(void)
{
        RW_PIN = 1;                     // Set the control bits for read
        RS_PIN = 0;
        DelayFor18TCY();
        E_PIN = 1;                      // Clock in the command
        DelayFor18TCY();

        if(DATA_PORT&0x80)					//if busy flag is set
        {
                E_PIN = 0;              // Reset clock line
                DelayFor18TCY();
                E_PIN = 1;              // Clock out other nibble
                DelayFor18TCY();
                E_PIN = 0;
                RW_PIN = 0;             // Reset control line
                return 1;               // Return TRUE
        }
        else                            // Busy bit is low
        {
                E_PIN = 0;              // Reset clock line
                DelayFor18TCY();
                E_PIN = 1;              // Clock out other nibble
                DelayFor18TCY();
                E_PIN = 0;
                RW_PIN = 0;             // Reset control line
                return 0;               // Return FALSE
        }

}

//*******************************************************************************


void OpenLCD(unsigned char lcdtype)
{
      
                          
        DATA_PORT &= 0x0f;
        TRIS_DATA_PORT &= 0x0F;

        TRIS_RW = 0;                    // All control signals made outputs
        TRIS_RS = 0;
        TRIS_E = 0;
        RW_PIN = 0;                     // R/W pin made low
        RS_PIN = 0;                     // Register select pin made low
        E_PIN = 0;                      // Clock pin made low

        // Delay for 15ms to allow for LCD Power on reset
        DelayPORLCD();
 //-------------------reset procedure through software----------------------       
		 WriteCmdLCD(0x30);
		 Delay10KTCYx(0x05);

		 WriteCmdLCD(0x30);
		 Delay10KTCYx(0x01);


		 WriteCmdLCD(0x32);
		 while( BusyLCD() );
//------------------------------------------------------------------------------------------


        // Set data interface width, # lines, font
        while(BusyLCD());              // Wait if LCD busy
        WriteCmdLCD(lcdtype);          // Function set cmd

        // Turn the display on then off
        while(BusyLCD());              // Wait if LCD busy
        WriteCmdLCD(DOFF&CURSOR_OFF&BLINK_OFF);        // Display OFF/Blink OFF
        while(BusyLCD());              // Wait if LCD busy
        WriteCmdLCD(DON&CURSOR_ON&BLINK_ON);           // Display ON/Blink ON

        // Clear display
        while(BusyLCD());              // Wait if LCD busy
        WriteCmdLCD(0x01);             // Clear display

        // Set entry mode inc, no shift
        while(BusyLCD());              // Wait if LCD busy
        WriteCmdLCD(SHIFT_CUR_LEFT);   // Entry Mode

        // Set DD Ram address to 0
        while(BusyLCD());              // Wait if LCD busy
        SetDDRamAddr(0x80);                // Set Display data ram address to 0

        return;
}

//******************************************************************************************

void putsLCD(char *buffer)
{
        while(*buffer)                  // Write data to LCD up to null
        {
                while(BusyLCD());      // Wait while LCD is busy
                WriteDataLCD(*buffer); // Write character to LCD
                buffer++;               // Increment buffer
        }
        return;
}

//*******************************************************************************************

unsigned char ReadAddrLCD(void)
{
        char data;                      // Holds the data retrieved from the LCD



        RW_PIN = 1;                     // Set control bits for the read
        RS_PIN = 0;
        DelayFor18TCY();
        E_PIN = 1;                      // Clock data out of the LCD controller
        DelayFor18TCY();                      
        data = DATA_PORT&0xf0;          // Read the nibble into the upper nibble of data
        E_PIN = 0;                      // Reset the clock
        DelayFor18TCY();
        E_PIN = 1;                      // Clock out the lower nibble
        DelayFor18TCY();
        data |= (DATA_PORT>>4)&0x0f;    // Read the nibble into the lower nibble of data
        E_PIN = 0;
        RW_PIN = 0;                     // Reset the control lines

        return (data&0x7f);             // Return the address, Mask off the busy bit
}

//********************************************************************************************

void SetDDRamAddr(unsigned char DDaddr)
{


        TRIS_DATA_PORT &= 0x0f;                 // Make port output
        DATA_PORT &= 0x0f;                      // and write upper nibble
        DATA_PORT |= ((DDaddr | 0b10000000) & 0xf0);

        RW_PIN = 0;                             // Set control bits
        RS_PIN = 0;
        DelayFor18TCY();
        E_PIN = 1;                              // Clock the cmd and address in
        DelayFor18TCY();
        E_PIN = 0;

        DATA_PORT &= 0x0f;                      // Write lower nibble
        DATA_PORT |= ((DDaddr<<4)&0xf0);

        DelayFor18TCY();
        E_PIN = 1;                              // Clock the cmd and address in
        DelayFor18TCY();
        E_PIN = 0;
        
        TRIS_DATA_PORT |= 0xf0;                 // Make port input


        return;
}

//**********************************************************************************************

void WriteCmdLCD(unsigned char cmd)
{

        TRIS_DATA_PORT &= 0x0f;
        DATA_PORT &= 0x0f;
        DATA_PORT |= cmd&0xf0;

        RW_PIN = 0;                     // Set control signals for command
        RS_PIN = 0;
        DelayFor18TCY();
        E_PIN = 1;                      // Clock command in
        DelayFor18TCY();
        E_PIN = 0;
        
        DATA_PORT &= 0x0f;
        DATA_PORT |= (cmd<<4)&0xf0;

        DelayFor18TCY();
        E_PIN = 1;                      // Clock command in
        DelayFor18TCY();
        E_PIN = 0;

        TRIS_DATA_PORT |= 0xf0;

        return;
}

//**********************************************************************************************

void WriteDataLCD(char data)
{


        TRIS_DATA_PORT &= 0x0f;
        DATA_PORT &= 0x0f;
        DATA_PORT |= data&0xf0;

        RS_PIN = 1;                     // Set control bits
        RW_PIN = 0;
        DelayFor18TCY();
        E_PIN = 1;                      // Clock nibble into LCD
        DelayFor18TCY();
        E_PIN = 0;

        DATA_PORT &= 0x0f;
        DATA_PORT |= ((data<<4)&0xf0);

        DelayFor18TCY();
        E_PIN = 1;                      // Clock nibble into LCD
        DelayFor18TCY();
        E_PIN = 0;

        TRIS_DATA_PORT |= 0xf0;

        return;
}