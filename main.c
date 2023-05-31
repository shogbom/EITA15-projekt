 /*
 * main.c
 *
 * Created: 2023-04-30 15:17:59
 * Author : Samuel
 */ 



#include <avr/io.h> // IO definitions 



uint8_t direction;

void init(){
	// pb3, pb4, pb6, pb7 pointing out.
	DDRB |= (1 << DDRB3) | (1 << DDRB4) | (1 << DDRB6) | (1 << DDRB7);
	// Setting baud rate to 9600 Baud.
	UBRR0 = 6;
	// turning on receiver 0 (rx0).
	UCSR0B |= (1 << RXEN0); 
}

uint8_t receive(){
	// wait for data
	while(!(UCSR0A & (1<<RXC0)));
	// return data.
	return UDR0;
}

void move(uint8_t data){
	if(data == 1){ /* fram */
		PORTB |= (0 << PINB3) | (0 << PINB4) | (1 << PINB6) | (1 << PINB7);
	}
	else if(data == 2){ /* hoger */
		PORTB |= (1 << PINB3) | (0 << PINB4) | (0 << PINB6) | (0 << PINB7);
	}
	else if(data == 3){ /* bak */
		PORTB |= (1 << PINB3) | (1 << PINB4) | (0 << PINB6) | (0 << PINB7);
	}
	else if(data == 4){ /* vanster */
		PORTB |= (0 << PINB3) | (1 << PINB4) | (0 << PINB6) | (0 << PINB7);
	}
	
	else PORTB = 0x00;
}


int main(void)
{
	init();
	while (1)
	{
		direction = receive();
		move(direction);
	}
}
