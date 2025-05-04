#include <xc.h>

#pragma config OSC = HS 
#pragma config WDT = OFF 
#pragma config LVP = OFF 
#pragma config PBADEN = OFF 

#pragma idata
unsigned char string1[]={"\n\rPC Communication"};
unsigned char string2[]={"\n\rOn-chip USART Test Code"};
unsigned char string3[]={"\n\rSend 10 character to uC\n\r"};
unsigned char string4[]={"\n\rTransmitted Characters are:"};
unsigned char string5[]={"\n\rRx Tx test complete\n\r"};

void TXbyte(unsigned char data); 
void TXstring (unsigned char *string); 

void main()
{
 unsigned char  i=0;
 unsigned char rx_data [20]; 
 TRISCbits.TRISC7=1; 
 TRISCbits.TRISC6=0; 
 SPBRG = 0x07;
 SPBRGH = 0x02;      
 TXSTA = 0x24;       
 RCSTA = 0x90;       
 BAUDCON = 0x08;     
 
 TXstring (string1); 
 TXstring (string2); 
 TXstring (string3); 
 for (i=0; i<10; i++)
	{	
 		while(PIR1bits.RCIF==0); 
			 rx_data [i]= RCREG; 
    }   
rx_data [10]= 0;	
TXstring (string4);	
TXstring (rx_data);	
TXstring (string5);	
 while(1);		
}

void TXbyte(unsigned char data)
{
    while(TXSTAbits.TRMT==0);		
    TXREG = data;					
}

void TXstring(unsigned char *string)
{
	unsigned char i=0;
 	for(i=0;string[i]!='\0';i++) 
 		TXbyte(string[i]);			
}