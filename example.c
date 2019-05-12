// You can compile this by running the command
//	gcc example.c src/wiringbeagle.h src/wiringbeagle.c
// Afterwards you only need to compile the example portion. 

#include <stdio.h> // printf
#include <unistd.h> // sleep function
#include "src/wiringbeagle.h"

int main() {
	int i;
	i = pinMode(67, OUTPUT);
	
	printf("pinMode status should be 0 if successful: %i\n", i);
	
	// turns pin off (sets value to 1)
	digitalWrite(67, HIGH);

	sleep(3);

	// turns pin off (sets value to 0)
	digitalWrite(67, LOW);

	// optional, undoes pinMode
	pinMode(67, UNEXPORT);

}
