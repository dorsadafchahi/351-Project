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
#include "LEDmatrix.h"

#define WATERSENSOR1 "/sys/bus/iio/devices/iio:device0/in_voltage1_raw"
#define WATERSENSOR2 "/sys/bus/iio/devices/iio:device0/in_voltage2_raw"

//function to get voltage reading from water sensor
double sampleInVolts(int SensorNum);

// Begin/end the background thread which samples water pollution levels.
void *waterSampler_start(int SensorNum);

//thead function to run in tandem with start sampling, that, with the help of mutexes, will analyze the array after it is filled
void *Sampler_startAnalysis();

//convert the 4095 number to voltage
double convertToVoltage(double number);

#endif