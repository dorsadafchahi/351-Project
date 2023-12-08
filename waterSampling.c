#include "waterSampling.h"

//array for water sample values
double waterValues[2][1000];//dirty = 1, clean = 2

//variables for storing sensor-percentage values
int SensorVal1 = 0;
int SensorVal2 = 0;
int PercentVal1 = 0;
int PercentVal2 = 0;
double AvgVal1 = 0;
double AvgVal2 = 0;
infoSens *s;

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
        printf("ERROR: Sensor 1 or 2 only\n");
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

void *waterSampler_start(void *SensorNumber)
{
    long long startTime = getTimeInMs();

    double value;
    int buffernum[2] = {0,0};//indeexes for dirty(1) and clean(2) arrays, starting at 0

    int SensorNum = (int)SensorNumber;

    // start sampling here for 5 seconds
    printf("Starting sampling: Wait for 5 seconds in sensor %d...\n\n", SensorNum);
    while (getTimeInMs() < (startTime + 5000))
    {
        value = sampleInVolts(SensorNum);//sample from which sensor

        // store values in the array based on which watersensor file
        waterValues[SensorNum-1][buffernum[SensorNum-1]] = value;
        buffernum[SensorNum-1]++;
        sleepForMs(5);
    }
    printf("Done sampling: Total of %d samples collected.\n", buffernum[SensorNum-1]);

    int percentage = calculatePercentagePollution(SensorNum, buffernum[SensorNum-1]);

    //store percentage values for later access
    if (SensorNum == 1) {
        SensorVal1 = SensorNum;
        PercentVal1 = percentage;
    } else if (SensorNum == 2) {
        SensorVal2 = SensorNum;
        PercentVal2 = percentage;
    }

    return NULL;
}

int calculatePercentagePollution(int SensorNum, int num_array){
    //after sampling for 5 seconds, do analysis on percentage pollution within the samples
    //and display that on the relevant LED
    double total;
    for (int i = 0; i < num_array; i++){
        total = waterValues[SensorNum-1][i] + total;
    }
    double average = total / num_array;

    //store average values for later access
    if (SensorNum == 1) {
        AvgVal1 = average;
    } else if (SensorNum == 2) {
        AvgVal2 = average;
    }
 
    //do a calculation here to find percentage... %100 = TOTALLY DIRTY, %0 = CLEANEST WATER ON EARTH
    //we are expecting a value from 0 - 3300 around ~
    int percentage = 100 - (int)((average / 3300.0) * 100);
    if (percentage <= 0) { //if percent is negative value, make 0 instead (due to high avg above our max range)
        percentage = 0;
    }

    printf("Calculating percentage (Sensor %d)...\n     Average: %f\n     Sample is %d percent dirty.\n\n", SensorNum, average, percentage);
    return percentage;
}

void displayOnLCD(infoSens *s) {
    // printf("\n\nDISPLAY: Sensor %d: %d, Sensor %d: %d\n", SensorVal1, PercentVal1, SensorVal2, PercentVal2); //uncomment for debugging
    //store percentage value in respected sensor for LCD
    s->infoSen1 = SensorVal1;
    s->infoSen2 = SensorVal2;
    s->infoPerc1 = PercentVal1;
    s->infoPerc2 = PercentVal2;
    s->infoAvg1 = AvgVal1;
    s->infoAvg2 = AvgVal2;
}
