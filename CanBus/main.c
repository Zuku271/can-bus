/*
 * CanBus.c
 *
 * Created: 2017-12-15 20:10:32
 * Author : Adrian
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "inc/uart.h"


volatile unsigned char odb_x;       
volatile unsigned char odb_flaga = 0;


         
char usart_bufor[16] = "A";


void main(void)
{
    UART_init();
	sei();
	UART_send(usart_bufor);
    while (1) 
    {
    }
}

ISR(USART_UDRE_vect)
{
	static volatile unsigned int usart_bufor_ind = 0;

	if(usart_bufor[usart_bufor_ind] != 0)
	{
		UDR = usart_bufor[usart_bufor_ind++];
	}
	else
	{
		UCSRB &= ~( 1 << UDRIE );
	}
}