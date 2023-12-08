#include "gpio.h"

static void writeToFile(const char* fileName, const char* value)
{
	FILE *pFile = fopen(fileName, "w");
	fprintf(pFile, "%s", value);
	fclose(pFile);
}

void GPIO_writeDirection(int gpio, char* dir)
{
    char* fileName;

    switch (gpio) {
        case D4_GPIO_NUMBER:
            fileName = D4_DIRECTION;
            break;
        case D5_GPIO_NUMBER:
            fileName = D5_DIRECTION;
            break;
        case D6_GPIO_NUMBER:
            fileName = D6_DIRECTION;
            break;
        case D7_GPIO_NUMBER:
            fileName = D7_DIRECTION;
            break;
        case RS_GPIO_NUMBER:
            fileName = RS_DIRECTION;
            break;
        case E_GPIO_NUMBER:
            fileName = E_DIRECTION;
            break;
    }
    writeToFile(fileName, dir);
}

void GPIO_writeValue(int gpio, char* val)
{
    char* fileName;

    switch (gpio) {
        case D4_GPIO_NUMBER:
            fileName = D4_VALUE;
            break;
        case D5_GPIO_NUMBER:
            fileName = D5_VALUE;
            break;
        case D6_GPIO_NUMBER:
            fileName = D6_VALUE;
            break;
        case D7_GPIO_NUMBER:
            fileName = D7_VALUE;
            break;
        case RS_GPIO_NUMBER:
            fileName = RS_VALUE;
            break;
        case E_GPIO_NUMBER:
            fileName = E_VALUE;
            break;
    }
    writeToFile(fileName, val);
}
