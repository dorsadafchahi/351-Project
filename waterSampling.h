// waterSampling.h
// Module to sample water pollution levels in the background (thread).
// It provides access to the raw voltage samples of the turbidity module

#ifndef WATER_SAMPLING_H
#define WATER_SAMPLING_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>
#include "time.h"
#include "lcd.h"

#define WATERSENSOR1 "/sys/bus/iio/devices/iio:device0/in_voltage5_raw"
#define WATERSENSOR2 "/sys/bus/iio/devices/iio:device0/in_voltage6_raw"

typedef struct {
    int infoSen1;
    int infoSen2;
    int infoPerc1;
    int infoPerc2;
    double infoAvg1;
    double infoAvg2;
} infoSens;

// function to get voltage reading from water sensor
double sampleInVolts(int SensorNum);

// Begin/end the background thread which samples water pollution levels.
void *waterSampler_start(void *SensorNumber);

// function to calculate the percentage of cleanliness in the water Samples, 0 = not clean, 100 = totally clean
int calculatePercentagePollution(int SensorNum, int num_array);

// function will help display values on LCD without noise or garbage output
void displayOnLCD(infoSens *s);

#endif