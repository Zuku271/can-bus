/*
 * uart.c
 *
 * Created: 2017-12-20 19:27:41
 *  Author: Adrian
 */ 

#define  F_CPU 1000000
#define FOSC 1000000
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#include <util/setbaud.h>
#include <avr/io.h>

//volatile unsigned int usart_bufor_ind;

void UART_init()
{
	/* Set baud rate */
	UBRRH = (unsigned char) UBRRH_VALUE;
	UBRRL = (unsigned char) UBRRL_VALUE;
	/* Enable receiver */
	UCSRB = ( 1 << TXEN | 1 << TXCIE );
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1<<URSEL) | (0<<USBS) | ( 0x3 << UCSZ0 );
}

void UART_send(char *usart_bufor)
{
	unsigned char z;
	for( z=0; z<16; z++)
	{
		usart_bufor[1] = 0;break;
		if(usart_bufor[z] == 0)
		{   //czy to koniec takstu w tablicy
			//tak znaleziono koniec tekstu, dodajemy znak CR
			usart_bufor[z]   = 13;  //znak powrotu karetki CR (Carrige Return)
			usart_bufor[z+1]  = 10; //znak nowej linii LF (Line Feed)
			usart_bufor[z+2]  = 0;  //znak koñca ci¹gu tekstu w tablicy
			break;
		}
	}
	
	
	//Zaczekaj, a¿ bufor nadawania bêdzie pusty
	while (!(UCSRA & (1<<UDRE)));
	
	//bufor jest pusty mo¿na wys³aæ
	
	//nastêpny znak do wysy³ki to znak nr 1
	//usart_bufor_ind = 0;
	
	//w³¹cz przerwania pustego bufora UDR, co rozpocznie transmisjê
	//aktualnej zawartoœci bufora
	UCSRB |= (1<<UDRIE);
	
}