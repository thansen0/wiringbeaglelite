# WiringBeagle Lite

Despite it's popularity and age, I wasn't able to find an easy to use GPIO for the beaglebone, so wrote my own. This project is intended to to be a stand-alone file and require no additional package instalations other than default C.

## What this is not

This is not a fully-fledged GPIO library, nor does it give you deep insight into GPIO functionality or useability. If you're hoping it'll be as exceptionally capable as wiringpi for beaglebone you're going to be dissapointed. This project simply writes to the hardware overlays, so if you're trying to change the pin readings at a high rate of speed you may encounter difficulties as well.

## What this is

This library is meant to be reminiscent of Arduino GPIO interaction, meaning it has a pinMode(), digitalWrite(), and digitalRead() function. It's meant to be self-contained in a single .c and .h file, and it's meant to be easily modified if the user wants to add functionality or modify functionality in some way. It's also very portable, meaning this library would probably work on most debian-based boards, but again I haven't tested it there. 

My goal with this code is just to save people the few hours it takes to learn what GPIO pins are and get them running, as well as make this familiar to people who have used Arduino in the past.

## What's coming

I'm currently adding PWM functionality. The functionality is designed to work with post-linux kernel 4.14, as beagblebone changed the implementation, breaking many of the currentPWM libraries. This functionality isn't quite finished, as pin 42 won't work (it's not build using the same hardward overlay) and I'm still having version issues with a few pins. PWM functions are in this current version however it should be fully up and running in the next week or two.

## How to install it

There are no libraries to install, since this is just two files. Just add the files to your working directory and include the header `#include "wiringbeagle.h"`. That should be it. 

## How to use the GPIO pins

The libraries are set up the same as with Arduio. You need to initialize the pin with `pinMode(int pin, int mode)`, where `mode` is either `OUTPUT`, `INPUT`, `INPUT\_PULLUP`, or `UNEXPORT`. Each of these nodes initialize the GPIO pin and set the direction to their respective terms with the exception of `UNEXPORT`. This isn't available in arduino and it essentially turns off the pin and deletes the file structure. You don't have to do this after closing the program, since the OS will unexport them all when it reboots and there's nothing wrong with just leaving the pin unexported in the first place. If you don't know what it means to unexport it you probably don't have to worry about it.

After initializing the pin you can use `digitalWrite(int pin, short type)` to write either `HIGH` (1) or `LOW` (0) (for an OUTPUT pin) or use `digitalRead(int pin)` to read what the pin is reading, it returns the value in the value register for the pin.

There's an example in the example.c file and here's one in code:

```
#include <unistd.h> // for sleep function
#include "src/wiringbeagle.h" // if the .h and .c files are in the same folder no need for src/

int main() {

	int LED_pin = 67;

	pinMode(LED_pin, OUTPUT);

	while (true) {
		digitalWrite(LED_pin, HIGH);

		sleep(1);

		digitalWrite(LED_pin, LOW);
		
		sleep(1);
	}

}

```

## How to use the PWM pins (unfinished but may work for you)

The PWM pins also work in a similar mannar to arduino boards. The user must export the pin first using `pinMode(pin, PWMOUTPUT)`, and then they may using `analogWrite(pin, duty_cycle)`, which is out of a period of 255.

There is a second function added, analogWrite2(pin, period, duty\_cycle) (named as such since basic C doesn't allow overloading) which allows you to set the period as well as duty\_cycle. Both return -1 if the function has an error.

```

int main() {
	
	int pwm_pin = 14;

	pinMode(pwm_pin, PWMOUTPUT);

	int er = analogWrite(pwm_pin, 127);

	if (er < 0) {
		printf("Unable to enable pwm pin %i\n", pwm_pin);
	}

}

```

## Troubleshooting the PWM pins

Most of the issues that come with the PWM pins is that depending on the version you get a different file path, and so far I'm not sure how to tell which is which. If you're having problems with the PWM functionality not working, you can check out [this guide](https://github.com/beagleboard/bb.org-overlays/blob/master/examples/cape-unversal-pwm.txt) and [this one](https://stackoverflow.com/questions/50203064/pwm-on-beaglebone-black-v4-14) which are effectively how I'm doing it in the code. You can simply check where your files are and changed the hardcoded file-urls.

