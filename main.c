//this is the final project for class ENSC 351
//  Started Nov 20th 2023
//  Completed Dec 8th 2023
//  Nicholas H, Dorsa A, Lester P, Jim P
//
//  Description: Water pollution detection
//  Will use 2 turbidity sensors to detect pollution in 2 water samples (ideally before and after a filter), 
//  and then display that amount on an LED
//  will use modules, threads and Gpio/I2c access to the beaglebone

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>
#include "waterSampling.h"
#include "button.h"
#include "joystick.h"

pthread_t thread1;
pthread_t thread2;

int main() {

    infoSens SensorOutput;

    //Initialize matrix for numbers
    // runCommand("config-pin P9_18 i2c");
    // runCommand("config-pin P9_17 i2c");
    // runCommand("i2cset -y 1 0x70 0x21 0x00");
    // runCommand("i2cset -y 1 0x70 0x81 0x00");
    runCommand("config-pin p8.43 gpio"); //initialize the GPIO USER BUTTON
    initializeLCD(); //initialize (clear) LCD
    
    writetoFile("in");
    long long starttime = getTimeInMs();
    while(getTimeInMs() < (starttime + (1000 * 60 * 3))) { //this loop will run until 3 min of inactivity
        if (getUSERvalue() == 48){//button is pressed
             // printf("Starting Water Analysis\n");
            initializeLCD();
            writeMessage("Analyzing water,                        Please wait 5s..");
            //Run thread 1 to gather data from the first sensor and place it into array
            pthread_create(&thread1, NULL, &waterSampler_start, (void *)1);

            //Run thread 2 to gather data from the second sensor and place it into array
            pthread_create(&thread2, NULL, &waterSampler_start, (void *)2);

            //now both arrays are filled, and need to display percentage of pollution in each %100?
            //done in the thread functions
            pthread_join(thread1, NULL);
            pthread_join(thread2, NULL);

            //Display sensor information on LCD
            initializeLCD(); //clears LCD
            displayOnLCD(&SensorOutput);
            starttime = getTimeInMs(); //resets start time for use in loop
            while(1) {
                initializeLCD(); //clears LCD
                joystickInfo(&SensorOutput);
                if (getUSERvalue() == 48) {
                    initializeLCD();
                    break;
                }
                if (getTimeInMs() > (starttime + (1000 * 60 * 3))) {
                    goto END;
                }
            }
            
            //reset the start time to count from now
            starttime = getTimeInMs();
        }
    }
END:
    initializeLCD(); //clears LCD
    writeMessage("Goodbye!");
    return 0;
}
