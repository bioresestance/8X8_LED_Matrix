#include "p18cxxx.h"

#define DATA 	PORTB
#define GNE		PORTAbits.RA2
#define RDE		PORTAbits.RA1
#define BLE		PORTAbits.RA3
#define ROWE	PORTAbits.RA4
#define OE		PORTAbits.RA0
#define UP		PORTCbits.RC0
#define LF		PORTCbits.RC1
#define DN		PORTCbits.RC2
#define RT		PORTCbits.RC4


extern void LoadGN(unsigned char data);
extern void LoadRD(unsigned char data);
extern void LoadBL(unsigned char data);
extern void LoadRow(unsigned char data); 
extern void DrawMatrix(unsigned int t);
extern void Init(void);
extern void ShiftUp(void);
extern void ShiftDown(void);
extern char Buttons(void);
extern void Collision(void);
extern void GenerateTerrain(void);
extern void SetRed( unsigned char Row, unsigned char Col);
extern void SetBlue( unsigned char Row, unsigned char Col);
extern void SetGreen( unsigned char Row, unsigned char Col);
extern void SetWhite( unsigned char Row, unsigned char Col);
extern void SetPurple( unsigned char Row, unsigned char Col);
extern void SetOrange( unsigned char Row, unsigned char Col);
extern void SetCyan( unsigned char Row, unsigned char Col);
extern void ClearAll( void );
extern void ClearOne( unsigned char Row, unsigned char Col);




