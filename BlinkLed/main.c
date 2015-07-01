/*
 * main.c
 *
 *  Created on: 13 mei 2015
 *      Author: SuperJoot
 */
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

int main(void){
 DDRB = 0b11111111;

 while(1)
 {
  PORTB = 0b11111110;
  _delay_ms(100);
  PORTB = 0b11111111;
  _delay_ms(100);
 }

}

