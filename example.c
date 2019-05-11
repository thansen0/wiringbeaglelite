#include <stdio.h> // printf
#include <unistd.h> // sleep function
#include "src/wiringbeagle.h"

int main() {
	int i;
	i = pinMode(67, OUTPUT);
	
	printf("Pinmode: %i\n", i);

	digitalWrite(67, HIGH);

	sleep(2);

	digitalWrite(67, LOW);

	pinMode(67, UNEXPORT);
}
