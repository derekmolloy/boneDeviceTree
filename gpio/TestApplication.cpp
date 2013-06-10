/*
 * TestApplication.cpp
 *
 * Copyright Derek Molloy, School of Electronic Engineering, Dublin City University
 * www.derekmolloy.ie
 *
 * YouTube Channel: http://www.youtube.com/derekmolloydcu/
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED ''AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL I
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <iostream>
#include <string>
#include <unistd.h>
#include "SimpleGPIO.h"
using namespace std;

unsigned int LEDGPIO = 60;   // GPIO1_28 = (1x32) + 28 = 60
unsigned int ButtonGPIO = 15;   // GPIO0_15 = (0x32) + 15 = 15

int main(int argc, char *argv[]){

	cout << "Testing the GPIO Pins" << endl;

        gpio_export(LEDGPIO);    // The LED
	gpio_export(ButtonGPIO);   // The push button switch
        gpio_set_dir(LEDGPIO, OUTPUT_PIN);   // The LED is an output
	gpio_set_dir(ButtonGPIO, INPUT_PIN);   // The push button input
	
	// Flash the LED 5 times
	for(int i=0; i<5; i++){
		cout << "Setting the LED on" << endl;
                gpio_set_value(LEDGPIO, HIGH);
		usleep(200000);         // on for 200ms
		cout << "Setting the LED off" << endl;
                gpio_set_value(LEDGPIO, LOW);
		usleep(200000);         // off for 200ms
	}

	// Wait for the push button to be pressed
	cout << "Please press the button!" << endl;

	unsigned int value = LOW;
	do {
		gpio_get_value(ButtonGPIO, &value); 
		cout << ".";
		usleep(1000);      // sleep for one millisecond
	} while (value!=HIGH);
	cout << endl <<  "Button was just pressed!" << endl;

	cout << "Finished Testing the GPIO Pins" << endl;
	gpio_unexport(LEDGPIO);     // unexport the LED
	gpio_unexport(ButtonGPIO);  // unexport the push button
	return 0;
}

