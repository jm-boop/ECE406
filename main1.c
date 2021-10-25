/*
 * ping-sd-usart-testing.c
 *
 * Created: 11/10/20 7:31:19 PM
 * Author : johnn
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 1000000 // factory default of 1MHz
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

void USART_Init( unsigned int );
void USART_Transmit( unsigned char );
unsigned char USART_Receive( void );

int main(void)
{
	unsigned char c;
	
    USART_Init(MYUBRR);
	
    while (1) 
    {
		c = USART_Receive();
		//sd print
		UCSR0A &= ~(1<<RXC0);
    }
}

void USART_Init( unsigned int ubrr )
{
	// Set the baud rate.
	// UBRR0 = USART Baud Rate Register
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)(ubrr);
	// Enable RX and TX
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	// Set frame format: 8data, 2stop bit
	UCSR0C = (1<<USBS0) | (3<<UCSZ00);
}

void USART_Transmit( unsigned char data )
{
	// Wait for empty transmit buffer by checking UDRE0 flag
	while ( !( UCSR0A & (1<<UDRE0)) )
	// Put data into buffer, sends the data
	UDR0 = data;
}

unsigned char USART_Receive( void )
{
	// Wait for the data to be received
	while ( !(UCSR0A & (1<<RXC0)) )
	// Get and return received data from buffer
	return UDR0;
}
