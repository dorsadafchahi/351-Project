#include "waterSampling.h"

double waterValues1[1000];//dirty
double waterValues2[1000];//clean

// Grabs voltage value of the specified file
double sampleInVolts(int whichSensor)
{
    FILE *voltage_file;
    if (whichSensor == 1){
        voltage_file = fopen(WATERSENSOR1, "r");
    }
    else if (whichSensor == 2){
        voltage_file = fopen(WATERSENSOR2, "r");
    }
    else{
        printf("error, sensor 1 or 2 only\n");
        return 1;
    }

    if (!voltage_file)
    {
        printf("ERROR: Unable to open voltage input file\n");
        exit(-1);
    }
    int value = 0;
    fscanf(voltage_file, "%d", &value);
    fclose(voltage_file);
    double val = value;
    return val;
}

void *waterSampler_start(int SensorNum)
{
    long long startTime = getTimeInMs();

    double value;
    double voltage;
    int buffernum1 = 0;//index or the array 1
    int buffernum2 = 0;//index for the array 2

    // start sampling here for 5 seconds
    while (getTimeInMs() < (startTime + 5000))
    {
        value = sampleInVolts(SensorNum);//sample from which sensor
        voltage = convertToVoltage(value);
        //printf("val=%f, volt=%f\n", value, voltage);

        // store values in the array based on which watersensor file
        if (SensorNum == 1){//dirty water
            waterValues1[buffernum1] = voltage;
            buffernum1++;
        }
        else if (SensorNum == 2){//clean water
            waterValues2[buffernum2] = voltage;
            buffernum2++;
        }
        sleepForMs(10);
    }

    //after sampling for 5 seconds, do analysis on percentage pollution within the samples
    //and display that on the relevant LED
    double total;
    if (SensorNum == 1){//dirty water
        for (int i = 0; i < buffernum1; i++){
            total = waterValues1[i] + total;
        }
        double average = total / buffernum1;
    }
    else if (SensorNum == 2){//clean water
        for (int j = 0; j < buffernum2; j++){
            total = waterValues2[j] + total;
        }
        double average = total / buffernum2;
    }
    
    //do a calculation here to find percentage... %100 = TOTALLY DIRTY, %0 = CLEANEST WATER ON EARTH
    //we are expecting a value from 0 - 3300 around ~

    return NULL;-
}
