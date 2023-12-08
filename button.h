#ifndef BUTTON_H
#define BUTTON_H

#include <stdio.h>
#include <stdlib.h>
#include "time.h"

#define USER_BUTTON_VALUE "/sys/class/gpio/gpio72/value"
#define USER_BUTTON_DIRECTION  "/sys/class/gpio/gpio72/direction"

int getUSERvalue();
void writetoFile(const char* value);

#endif