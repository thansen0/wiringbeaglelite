
#ifndef I2C_INTERFACE_HPP
#define I2C_INTERFACE_HPP

#include <stdio.h>
#include <stdlib.h> // malloc
#include <string.h> // strcat and strcpy

#define OUTPUT 1
#define INPUT 2
#define INPUT_PULLUP 3 // NOT IMPLENTED
#define UNEXPORT 4

#define HIGH 1
#define LOW 0

char* itostr(int n);

// VerifyPin returns an allocated string. You MUST
// free it
short verifyPin(int pin);

int pinMode(int pin, short mode);

int digitalWrite(int pin, short type);

int digitalRead(int pin); // not implemented

#endif
