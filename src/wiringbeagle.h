
#ifndef GPIO_BBB_INTERFACE_H
#define GPIO_BBB_INTERFACE_H

#include <stdio.h>
#include <stdlib.h> // malloc
#include <string.h> // strcat and strcpy
#include <unistd.h> // sllep

#define OUTPUT 1
#define INPUT 2
#define INPUT_PULLUP 3 // NOT IMPLENTED
#define UNEXPORT 4

#define HIGH 1
#define LOW 0

// User MUST free returned string, since the string is
// allocated in the heap. Otherwise you will notice a
// suspicious amount of ram dissapear
// char* itostr(int n);

// returns a 0 or 1 based on whether the pin lies
// within the predicted range for the beaglebone black
// short verifyPin(int pin);

/* Sets the pin mod for the pin. Acceptable modes are
 *	OUTPUT
 *	INPUT
 * 	UNEXPORT
 */
int pinMode(int pin, short mode);

/*
 * Writes a HIGH or LOW value to the pin, turning the
 * GPIO pin on or off. User must set pin to OUTPUT 
 * before they are able to write using digitalWrite.
 *
 */
int digitalWrite(int pin, short type);

// Not implemented yet
int digitalRead(int pin);

#endif
