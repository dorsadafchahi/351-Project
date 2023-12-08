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

pthread_t thread1;
pthread_t thread2;

//comment

int main() {

    // int SensorVal = 0;
    // int PercentVal = 0;
    // char percentStr[16];
    infoSens SensorOutput;
    char result[32];

    //Initialize matrix for numbers
    // runCommand("config-pin P9_18 i2c");
    // runCommand("config-pin P9_17 i2c");
    // runCommand("i2cset -y 1 0x70 0x21 0x00");
    // runCommand("i2cset -y 1 0x70 0x81 0x00");
    initializeLCD();

    // printf("Starting Water Analysis\n");
    writeMessage("Analyzing water");

    // for (int i = 0; i < 1000; i++{
    //     printf("A2D value: %f\n", sampleInVolts(1));
        
    // })
    //Run thread 1 to gather data from the first sensor and place it into array
    pthread_create(&thread1, NULL, &waterSampler_start, (void *)1);

    // //Run thread 2 to gather data from the second sensor and place it into array
    pthread_create(&thread2, NULL, &waterSampler_start, (void *)2);


    //now both arrays are filled, and need to display percentage of pollution in each %100?
    //done in the thread functions

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    //Display sensor information on LCD
    initializeLCD(); //clears LCD
    displayOnLCD(&SensorOutput);
    // printf("\n\nSensor %d: %d, Sensor %d: %d\n", SensorOutput.infoSen1, SensorOutput.infoPerc1, SensorOutput.infoSen2, SensorOutput.infoPerc2);

    snprintf(result, sizeof(result), "Blue:%d  Blk:%d  ", SensorOutput.infoPerc2, SensorOutput.infoPerc1);
    writeMessage(result);

    return 0;
}