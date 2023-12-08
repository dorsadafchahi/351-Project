// this is the final project for class ENSC 351
//   Started Nov 20th 2023
//   Completed Dec 8th 2023
//   Nicholas H, Dorsa A, Lester P, Jim P
//
//   Description: Water pollution detection
//   Will use 2 turbidity sensors to detect pollution in 2 water samples (ideally before and after a filter),
//   and then display that amount on an LED
//   will use modules, threads and Gpio/I2c access to the beaglebone

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>
#include "waterSampling.h"

pthread_t thread1;
pthread_t thread2;
pthread_t initialThread;

void *waterPollutionDetection(void *arg)
{
    infoSens SensorOutput;
    char result[32];

    while (1)
    {
        int flag = getGPIOvalue(72);
        // Check GPIO value if 48 then pressed
        if (flag == 48)
        {
            initializeLCD(); // Clear LCD and reset variables
            writeMessage("Analyzing water");

            pthread_create(&thread1, NULL, &waterSampler_start, (void *)1);
            pthread_create(&thread2, NULL, &waterSampler_start, (void *)2);

            pthread_join(thread1, NULL);
            pthread_join(thread2, NULL);

            initializeLCD(); // Clear LCD
            displayOnLCD(&SensorOutput);

            snprintf(result, sizeof(result), "Blue:%d  Blk:%d  ", SensorOutput.infoPerc2, SensorOutput.infoPerc1);
            writeMessage(result);
        }
    }
    return NULL;
}

int main()
{
    // //initialize the GPIO USER BUTTON
    GPIO_writeDirection(72, "out");

    // Create a thread for water pollution detection
    pthread_create(&initialThread, NULL, &waterPollutionDetection, NULL);

    // Other main tasks or code...

    pthread_join(initialThread, NULL);

    return 0;
}
