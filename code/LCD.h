#include "p18cxxx.h"

/* DATA_PORT defines the port to which the LCD data lines are connected */
 #define DATA_PORT      		PORTD
 #define TRIS_DATA_PORT 		TRISD

//CTRL_PORT defines the port where the control lines are connected.
 #define RW_PIN   LATDbits.LATD1   		/* PORT for RW */
 #define TRIS_RW  TRISDbits.TRISD1    	/* TRIS for RW */

 #define RS_PIN   LATDbits.LATD0   		/* PORT for RS */
 #define TRIS_RS  TRISDbits.TRISD0    	/* TRIS for RS */

 #define E_PIN    LATDbits.LATD2  		/* PORT for E  */
 #define TRIS_E   TRISDbits.TRISD2   	/* TRIS for E  */
 
 #define Busy_Flag   LAT			/* Busy Flag       */

/* Display ON/OFF Control defines */
#define DON         0b00001111  /* Display on      */
#define DOFF        0b00001011  /* Display off     */
#define CURSOR_ON   0b00001111  /* Cursor on       */
#define CURSOR_OFF  0b00001101  /* Cursor off      */
#define BLINK_ON    0b00001111  /* Cursor Blink    */
#define BLINK_OFF   0b00001110  /* Cursor No Blink */


/* Cursor or Display Shift defines */
#define SHIFT_CUR_LEFT    0b00010011  /* Cursor shifts to the left   */
#define SHIFT_CUR_RIGHT   0b00010111  /* Cursor shifts to the right  */
#define SHIFT_DISP_LEFT   0b00011011  /* Display shifts to the left  */
#define SHIFT_DISP_RIGHT  0b00011111  /* Display shifts to the right */

/* Function Set defines */
#define FOUR_BIT   0b00101100  /* 4-bit Interface               */
#define EIGHT_BIT  0b00111100  /* 8-bit Interface               */
#define LINE_5X7   0b00110000  /* 5x7 characters, single line   */
#define LINE_5X10  0b00110100  /* 5x10 characters               */
#define LINES_5X7  0b00101000  /* 5x7 characters, multiple line */

#define PARAM_SCLASS auto
#define MEM_MODEL far  /* Change this to near for small memory model */

/* OpenXLCD
 * Configures I/O pins for external LCD
 */
extern void OpenLCD(PARAM_SCLASS unsigned char);

/* SetDDRamAddr
 * Sets the display data address
 */
extern void SetDDRamAddr(PARAM_SCLASS unsigned char);

/* BusyXLCD
 * Returns the busy status of the LCD
 */
extern unsigned char BusyLCD(void);

/* ReadAddrXLCD
 * Reads the current address
 */
extern unsigned char ReadAddrLCD(void);

/* WriteCmdXLCD
 * Writes a command to the LCD
 */
extern void WriteCmdLCD(PARAM_SCLASS unsigned char);

/* putsXLCD
 * Writes a string of characters to the LCD
 */
extern void putsLCD(PARAM_SCLASS char *);

extern void WriteDataLCD(PARAM_SCLASS char data);

/* User defines these routines according to the oscillator frequency */
extern void DelayFor18TCY(void);

extern void DelayPORLCD(void);

extern void DelayLCD(void);

