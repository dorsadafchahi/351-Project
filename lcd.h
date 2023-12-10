// lcd.h
// Module for defining and initializing LCD functionality
// Setup for LCD is done here, along with 4-bit char conversion
// Referenced from Brian Fraser's 16x2 LCD How-To Guide

#ifndef _LCD_H_
#define _LCD_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include "gpio.h"

// nanosleep wrapper function - accepts seconds and nanoseconds to construct delay
void delayFor(int, int);

// Flash the E pin high to low to have the LCD consume the data
void pulseEnable();

// Write 4 bits to their corresponding pin (D4, D5, D6, D7)
void write4Bits(uint8_t);

// Write a char to the LCD
void writeChar(char);

// Write a message to the LCD
void writeMessage(char* result);

// Initialize the LCD (clear)
void initializeLCD();

#endif