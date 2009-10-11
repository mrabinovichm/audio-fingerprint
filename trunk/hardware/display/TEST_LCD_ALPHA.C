/*
	Hardware definitions for alphanumeric LCD displays
	
		PA.0-7	I/O	LCD D0-7
	
		PE.0	Out	LCD E
		PE.4	Out	LCD RS
		PE.5	Out	LCD R/W_

		PE.1,7	Out	free and waiting
*/

/* LCD control signals */	
#define	LCD_E		0
#define	LCD_RS	4
#define	LCD_RW	5

/* LCD status bits */
#define BUSY	7


void MsDelay ( int iDelay )
{	unsigned long ul0;
	ul0 = MS_TIMER;		// get current timer value
	while ( MS_TIMER < ul0 + (unsigned long) iDelay );
}

void UsDelay ( int iDelay )
{	int i;
	iDelay /= 11;		// this is experimental, for a RCM2100
	for ( i=0; i<iDelay; i++ );
}


/* Low level functions */
	
void LCD_Write(int data)
{
	WrPortI ( PADR, &PADRShadow, data );		// write data
	WrPortI ( SPCR, &SPCRShadow, 0x84 );		// PA0-7 = Outputs, put data in bus
	BitWrPortI ( PEDR, &PEDRShadow, 0,LCD_RW );	// Lower RW (Write)
	BitWrPortI ( PEDR, &PEDRShadow, 1,LCD_E );	// Rise E
	BitWrPortI ( PEDR, &PEDRShadow, 0,LCD_E );	// Lower E
}

int LCD_Read()
{
int data;
	BitWrPortI ( PEDR, &PEDRShadow, 1,LCD_RW );	// Rise RW (Read)
	WrPortI ( SPCR, &SPCRShadow, 0x80 );		// PA0-7 = Inputs, remove data from bus
	BitWrPortI ( PEDR, &PEDRShadow, 1,LCD_E ); // Rise E
	data=RdPortI ( PADR );		   // read data
	BitWrPortI ( PEDR, &PEDRShadow, 0,LCD_E ); // Lower E
	return(data);
}

int LCD_Status()
{
int status;
	BitWrPortI ( PEDR, &PEDRShadow, 0,LCD_RS );	// Lower RS (Cmd)
	do {
		status=LCD_Read();		   // read status (busy flag+address)
	} while(status&(1<<BUSY));		// loop while busy=1
	return(status);
}

int LCD_ReadData()
{
	BitWrPortI ( PEDR, &PEDRShadow, 1,LCD_RS );	// Rise RS (Data)
	return(LCD_Read());
}

void LCD_WriteCmd(int cmd)
{
	LCD_Status();		// RS returns low
	LCD_Write(cmd);
}

void LCD_WriteData(int data)
{
	LCD_Status();
	BitWrPortI ( PEDR, &PEDRShadow, 1,LCD_RS );	// Rise RS (Data)
	LCD_Write(data);
}

void LCD_init ()
{
	WrPortI ( PEDR,&PEDRShadow,0x00 );		// Make sure Outputs are Low
	WrPortI ( PEDDR,&PEDDRShadow,'\B10110011' );	// PE0,1,4,5,7 = output
	WrPortI ( PEFR, &PEFRShadow, 0 );		// PE: no I/O strobe
	MsDelay ( 1000 );				// wait for LCD to reset itself

	LCD_WriteCmd ( '\B00111000' );			// 8 bit mode, 2 (or more) lines, 5x7
	LCD_WriteCmd ( '\B00000110' );			// incr address and shift cursor with each character
	LCD_WriteCmd ( '\B00001100' );			// turn on display, no cursor, non-blinking
}

/* High level functions */

void LCD_show ( char *ptr )
{
	while (*ptr)
		LCD_WriteData (*ptr++);
}

void LCD_at (unsigned int row, unsigned int col)
{
	const static char acPos[4] = { 0x80,0xC0,0x94,0xD4 };

		LCD_WriteCmd( acPos[row]+col );
}


void LCD_clear ( void )
{
	LCD_at(0,0);		//address 0
	LCD_WriteCmd (0x10);			// home
	LCD_WriteCmd (0x01);			// clear the display
}

LCD_defchar(int charadd, int *pattern)
{
int i;
	LCD_WriteCmd((charadd<<3)^0x40); // CGRAM address
	for(i=0;i<8;i++)
		LCD_WriteData(pattern[i]);
}

/* MAIN PROGRAM */

main()
{
int i;

const static int p1[]={0,0,0,0,0,0,0,0};
const static int p[][]={
	{0,0,0,0,0,0,0,0x1f},
	{0,0,0,0,0,0,0x1f,0x1f},
	{0,0,0,0,0,0x1f,0x1f,0x1f},
	{0,0,0,0,0x1f,0x1f,0x1f,0x1f},
	{0,0,0,0x1f,0x1f,0x1f,0x1f,0x1f},
	{0,0,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f},
	{0,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f},
	{0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f}
};

	LCD_init();
	LCD_clear();
	LCD_show("LCD test");
	LCD_at(1,0);
	LCD_show("- Cika -");
	MsDelay(1000);
	for(i=0;i<8;i++){
		LCD_WriteCmd('\B00011000'); //shift display left
		MsDelay(300);
	}	
	for(i=0;i<8;i++){
		LCD_WriteCmd('\B00011100'); //shift display right
		MsDelay(300);
	}	
	MsDelay(1000);
	LCD_defchar(0,p1); //clear char 0
	LCD_at(0,0);
	for(i=0;i<80;i++)
		LCD_WriteData(0); //fill DDRAM with user char 0	
	while(1){
		LCD_defchar(0,p1);
		MsDelay(200);
		for(i=0;i<8;i++){
			LCD_defchar(0,p[i]); //anim up
			MsDelay(200);
		}
		MsDelay(2000);
		for(i--;i>=0;i--){
			LCD_defchar(0,p[i]); //anim down
			MsDelay(200);
		}
		LCD_defchar(0,p1); //clear char 0
		MsDelay(200);
	}
}
