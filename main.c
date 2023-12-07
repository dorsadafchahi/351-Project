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

int main(){

    //Initialize matrix for numbers
    // runCommand("config-pin P9_18 i2c");
    // runCommand("config-pin P9_17 i2c");
    // runCommand("i2cset -y 1 0x70 0x21 0x00");
    // runCommand("i2cset -y 1 0x70 0x81 0x00");

    printf("Starting Water Analysis\n");
    
    for (int i = 0; i < 1000; i++{
        printf("A2D value: %f\n", sampleInVolts(1));
        
    })
    //Run thread 1 to gather data from the first sensor, and display average cleanliness on LED1 (%)
    // pthread_create(&thread1, NULL, &waterSampler_start, 1);

    // //Run thread 2 to gather data from the second sensor, and display average cleanliness on LED2 (%)
    // pthread_create(&thread2, NULL, &waterSampler_start, 2);



    return 0;
}test