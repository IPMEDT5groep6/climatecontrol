/*
 * main.c
 *
 *  Created on: 13 mei 2015
 *      Author: Martijn
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

//Comments toevoegen is super vet

int main() {
	DDRB = 0b11111111;

	while (1) {
		PORTB = 0b01111111;
		_delay_ms(5000);
		PORTB = 0b11111111;
		_delay_ms(5000);
		PORTB = 0b10111111;
		_delay_ms(5000);
		PORTB = 0b11111111;
		_delay_ms(5000);
	}
}
