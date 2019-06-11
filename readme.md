# WiringBeagle Lite

Despite it's popularity and age, I wasn't able to find an easy to use GPIO for the beaglebone, so wrote my own. This would probably work on a lot of debian-based boards with GPIO pins (including raspberry pi) however I haven't tested it with them.

## What this is not

This is not a fully-fledged GPIO library, nor does it give you deep insight into GPIO functionality or useability. If you're hoping it'll be like wiringpi for beaglebone you're going to be super dissapointed. It also isn't going to be super fast, so if you're trying to change the pin readings at a high rate of speed it won't work either.

## What this is

This library is meant to be reminiscent of Arduino GPIO interaction, meaning it has a pinMode(), digitalWrite(), and digitalRead() function. It's meant to be self-contained in a single .c and .h file, and it's meant to be easily modified if the user wants to add functionality or modify functionality in some way. It's also very portable, meaning this library would probably work on most debian-based boards, but again I haven't tested it there. 

My goal with this code is just to save people the few hours it takes to learn what GPIO pins are and get them running, as well as make this familiar to people who have used Arduino in the past.

## How to install it

There are no libraries to install, since this is just two files. Just add the files to your working directory and include the header `#include "wiringbeagle.h"`. That should be it. 

## How to use it 

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
