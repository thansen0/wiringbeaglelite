// You can compile this by running the command
//	gcc example.c src/wiringbeagle.h src/wiringbeagle.c
// Afterwards you only need to compile the example portion. 

#include <stdio.h> // printf
#include <unistd.h> // sleep function
#include "src/wiringbeagle.h"

void modify_GPIO_pin() {
	int i;
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

	printf("digitalRead in should be 0: %i\n", in);

	pinMode(pin, UNEXPORT);
}

void modify_PWM_pin() {
	printf("Modifying PWM pins\n");

	int pwm = 19;
	// ensures pin is initialized, BBB often initializes them by
	// default but this is still good practice
	pinMode(pwm, PWMOUTPUT);

	// writes PWM signal to be about half on, 127/255
	analogWrite(pwm, 127);

	sleep(3);

	// sets PWM all the way on
	analogWrite(pwm, 255);

	sleep(3);

	// turns PWM off
	analogWrite(pwm, 0);

	// we don't want to unexport the pins, as that can cause 
	// issues until reboot

	sleep(1);
}

int main() {

	modify_GPIO_pin();

	modify_PWM_pin();

	return 0;
}
