// joystick.h
// Module defines joystick functionality. Reads X/Y values for use in
// other functions that support UI and user output actions

#ifndef JOYSTICK_H
#define JOYSTICK_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "waterSampling.h"
#define JoyX "/sys/bus/iio/devices/iio:device0/in_voltage2_raw"
#define JoyY "/sys/bus/iio/devices/iio:device0/in_voltage3_raw"

// Reads joystick A2D value depending on position X/Y
double Joystick_readX();
double Joystick_readY();

// Returns current state of joystick when called
int getDirection();

// Function that outputs information dependent on joystick position
void joystickInfo(infoSens *sVal);

#endif