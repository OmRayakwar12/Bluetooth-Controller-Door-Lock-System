#include <reg52.h>
sbit relay = P2^0;   
// Function to initialize UART at 9600 baud rate (11.0592 MHz crystal)
void UART_Init() {
    TMOD = 0x20;      
    TH1 = 0xFD;       
    TL1 = 0xFD;
    TR1 = 1;          
    SCON = 0x50;      
    EA = 1;           
}
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 1275; j++);
}
void main() {
    char bt_data;

    UART_Init();       // Initialize serial communication

    // Initial states
    relay = 0;         // Relay OFF (door locked)
		while (RI == 0);        // Wait for Bluetooth data
        bt_data = SBUF;         // Read received character
        RI = 0;                 // Clear receive flag

        if(bt_data == '1') {
            relay = 1;          // Unlock door
            delay_ms(300);
            
        }
        else if(bt_data == '0') {
            relay = 0;          // Lock DOOR
            delay_ms(300);
            
        }
    
}
