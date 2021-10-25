#define F_CPU		8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "USART.h"

#define USART_BAUDRATE			9600
#define UBRR0_VALUE			(((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

int main(void){
	

	DDRB = 0b00000011;
	UBRR0H = (unsigned char)(UBRR0_VALUE>>8);
	UBRR0L = (unsigned char)UBRR0_VALUE;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8 data bit, 1 stop bit */
	UCSR0C = (3<<UCSZ00);
	
	unsigned int ch = 0x52;
	unsigned char chr;
	
	int x = 29;
	
	unsigned int data[6] = {0x30,0x31,0x32,0x33,0x34,0x21};
	
	while(1){
		chr = GPS_Receive();
		if(chr == 'B'){
			for(int i=0;i<6;i++){
				PING_Transmit(data[i]);
			}
			PORTB |= 0x03;
		}	
	}
	
	return 0;	
}

