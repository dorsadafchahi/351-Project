#ifndef _GPIO_H_
#define _GPIO_H_
#include <stdio.h>

#define D4_GPIO_NUMBER 66
#define D5_GPIO_NUMBER 69
#define D6_GPIO_NUMBER 115
#define D7_GPIO_NUMBER 48
#define RS_GPIO_NUMBER 68
#define E_GPIO_NUMBER  67

#define D4_DIRECTION "/sys/class/gpio/gpio66/direction"
#define D4_VALUE "/sys/class/gpio/gpio66/value"

#define D5_DIRECTION "/sys/class/gpio/gpio69/direction"
#define D5_VALUE "/sys/class/gpio/gpio69/value"

#define D6_DIRECTION "/sys/class/gpio/gpio115/direction"
#define D6_VALUE "/sys/class/gpio/gpio115/value"

#define D7_DIRECTION "/sys/class/gpio/gpio48/direction"
#define D7_VALUE "/sys/class/gpio/gpio48/value"

#define RS_DIRECTION "/sys/class/gpio/gpio68/direction"
#define RS_VALUE "/sys/class/gpio/gpio68/value"

#define E_DIRECTION "/sys/class/gpio/gpio67/direction"
#define E_VALUE "/sys/class/gpio/gpio67/value"

// Write the provided string "in"/"out" to the given GPIO's direction
void GPIO_writeDirection(int, char*);
// Write the provided string "1"/"0" to the given GPIO's value
void GPIO_writeValue(int, char*);

#endif