#include <xc.h>

#pragma config OSC=HS, WDT=OFF, LVP=OFF, PBADEN=OFF

void t(char c) {
    while (!TXSTAbits.TRMT);  
    TXREG = c;                
}

void main() {
    char r[10];               

    TRISC6 = 0;               
    TRISC7 = 1;               

    SPBRGH = 2;               
    SPBRG = 7;                
    TXSTA = 0x24;             
    RCSTA = 0x90;             
    BAUDCON = 8;              

    for (char i = 0; i < 10;) {
        if (PIR1bits.RCIF)    
            r[i++] = RCREG;   
    }

    for (char i = 0; i < 10; i++)
        t(r[i]);              

    while (1);                
}
