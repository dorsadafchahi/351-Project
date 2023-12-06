#include "waterSampling.h"

// Grabs voltage value of the specified file
double sampleInVolts(FILE WATERSENSOR)
{
    FILE *voltage_file = fopen(WATERSENSOR, "r");
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

void *waterSampler_start()
{
    // initialize array
    buffer_index = 0;

    buffer = (samplerDatapoint_t *)malloc(1000 * sizeof(samplerDatapoint_t));
    if (buffer == NULL)
    {
        printf("error: memory not allocated properly\n");
        exit(-1);
    }
    if (pthread_mutex_init(&mutexlock, NULL) != 0)
    {
        printf("mutex lock initialization failed\n");
        exit(-1);
    }
    prev_endtime = getTimeInMicroS();

    // start sampling here
    while (1)
    {
        double value;
        double voltage;
        value = sampleInVolts();
        voltage = convertToVoltage(value);
        // printf("val=%f, volt=%f\n", value, voltage);

        // this should only happen if thread2 is gonna stop, eg the button was pressed
        if (buffer_index > 900)
        {
            printf("Done shutdown! Goodbye!\n");
            return NULL;
        }

        // lock the mutex
        pthread_mutex_lock(&mutexlock);

        // store values in the struct
        buffer[buffer_index].sampleInV = voltage;
        buffer[buffer_index].getTimeInMicroSeconds = getTimeInMicroS();
        buffer_index++;

        // unlock the mutex, for the second thread to gain access if need be
        pthread_mutex_unlock(&mutexlock);

        sleepForMs(3);
    }
    return NULL;
}

void *Sampler_startAnalysis()
{
    // these are all the values we will calculate in this function for printf at the end
    double average_voltage = 0;
    double min_voltage = 0.9;
    double max_voltage = 0.9;
    long long average_time = 0;
    long long max_time = 0;
    long long min_time = 10000;
    int num_dips = 0;

    // lock the mutex for use
    pthread_mutex_lock(&mutexlock);
    // loop through entire buffer structure array for ALL CALCULATIONS
    for (int i = 0; i < buffer_index; i++)
    {
        // average voltage calculated
        average_voltage = calculate_averageV(i, average_voltage);

        // min and max voltage checked
        if (buffer[i].sampleInV < min_voltage)
        {
            min_voltage = buffer[i].sampleInV;
        }
        if (buffer[i].sampleInV > max_voltage)
        {
            max_voltage = buffer[i].sampleInV;
        }

        // calculate if there was a dip
        // needs to be adjusted
        if ((calculate_dip(i, average_voltage) == true) && (last_dip == false))
        {
            last_dip = true;
            num_dips++;
        } else if (last_dip == true) {
            if (calculate_dip(i, average_voltage) == false) {
                last_dip = false;
            }
        }

        // time analysis
        long long time_interval = 0;
        if (i == 0)
        {
            time_interval = (buffer[0].getTimeInMicroSeconds - prev_endtime);
        }
        else
        {
            time_interval = buffer[i].getTimeInMicroSeconds - buffer[i - 1].getTimeInMicroSeconds;
        }

        // average time intervals
        average_time = calculate_averageT(time_interval, average_time);

        // check for min max time interval
        if (time_interval < min_time)
        {
            min_time = time_interval;
        }
        if (time_interval > max_time)
        {
            max_time = time_interval;
        }

        if (i == (buffer_index - 1)) {
            prev_endtime = getTimeInMicroS();
        }
    }

    printf("Interval ms (%.3f, %.3f) avg=%.3f   Samples V (%.3f, %.3f) avg=%.3f   # Dips:   %d   # Samples:    %d\n", displayMicroToMs(min_time), displayMicroToMs(max_time), displayMicroToMs(average_time), min_voltage, max_voltage, average_voltage, num_dips, buffer_index);

    // reset the buffer_index to 0, to make the thread1 start from 0 filling the struct array
    buffer_index = 0;
    // unlock the mutex for use
    pthread_mutex_unlock(&mutexlock);

    // this is area where we display onto the LED matrix based on the joystick position
    int joystick_dir = getDirection();
    switch (joystick_dir)
    {
    case 0: // nothing
        // display num of dips on the LED
        displayInt(num_dips);
        break;
    case 1: // left
        // display min interval between times min_time
        displayDouble(displayMicroToMs(min_time));
        break;
    case 2: // right
        // display max interval between times max_time
        displayDouble(displayMicroToMs(max_time));
        break;
    case 3: // up
        // display max num of voltage max_V
        displayDouble(max_voltage);
        break;
    case 4: // down
        // display min num of voltage min_V
        displayDouble(min_voltage);
        break;
    }
    return NULL;
}

// convert voltage number 4095 to volts (1.4V eg)
double convertToVoltage(double number)
{
    double voltage = (number / 4095) * 1.8;
    return voltage;
}

// function to end
void Sampler_stopSampling()
{
    pthread_mutex_destroy(&mutexlock);
    free(buffer);
}
