// time.h
// Module that defines time functions for use in functions that
// depend on current time/state of beaglebone;
// eg. adding delay or creating autonomous loops

#ifndef TIME_H
#define TIME_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Get current time function
long long getTimeInMs(void);

// Add delay (in number of milliseconds)
void sleepForMs(long long delayInMs);

//given function to run a command on terminal
//given function to run a linux command in C
void runCommand(char* command);

#endif