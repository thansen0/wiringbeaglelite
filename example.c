// You can compile this by running the command
//	gcc example.c src/wiringbeagle.h src/wiringbeagle.c
// Afterwards you only need to compile the example portion. 

#include <stdio.h> // printf
#include <unistd.h> // sleep function
#include "src/wiringbeagle.h"

int main() {
	/*int i;
	int pin = 67;
	i = pinMode(pin, OUTPUT);
	
	printf("pinMode status should be 0 if successful: %i\n", i);

	// turns pin off (sets value to 1)
	digitalWrite(pin, HIGH);

	sleep(3);

	// turns pin off (sets value to 0)
	digitalWrite(pin, LOW);

	// optional, undoes pinMode
	pinMode(pin, UNEXPORT);

	// allow unexporting to process
	sleep(3);

	pinMode(pin, INPUT);

	int in = digitalRead(pin);

	printf("digitalRead in is 0: %i\n", in);

	pinMode(pin, UNEXPORT);
*/
	printf("Modifying PWM pins now\n");

	int pwm = 19;
	pinMode(pwm, PWMOUTPUT);

	analogWrite(pwm, 127);

	sleep(3);

	analogWrite(pwm, 255);

	sleep(3);

	analogWrite(pwm, 0);

	sleep(1);
}
