//this is the final project for class ENSC 351
//  Started Nov 20th 2023
//  Completed Dec 8th 2023
//  Nicholas H, Dorsa A, Lester P, Jim P
//
//  Description: Water pollution detection
//  Will use 2 turbidity sensors to detect the amount of pollution in 2 water samples (before and after filter), 
//  and then display that amount on an LED
//  will use modules, threads and Gpio/I2c access to the beaglebone

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>
#include "LEDmatrix.h"

pthread thread1;
pthread thread2;

int main(){

    //Initialize matrix for number


    printf("Starting Water Analysis\n");
    
    //Run thread 1 to gather data from the first sensor
    //pthread_create(&thread1, NULL, &Sampler_startSampling, NULL);

    //Run thread 2 to gather data from the second sensor
    //pthread_create(&thread2, NULL, &Sampler_startSampling, NULL);



    
    return 0;

}


//given function to run a linux command in C
void runCommand(char* command) {    
    // Execute the shell command (output into pipe)    
    FILE *pipe = popen(command, "r");    
    // Ignore output of the command; but consume it     
    // so we don't get an error when closing the pipe.    
    char buffer[1024];    
    while (!feof(pipe) && !ferror(pipe)) {        
        if (fgets(buffer, sizeof(buffer), pipe) == NULL)            
        break;        
        // printf("--> %s", buffer);  // Uncomment for debugging    
    }    
    // Get the exit code from the pipe; non-zero is an error:    
    int exitCode = WEXITSTATUS(pclose(pipe));    
    if (exitCode != 0) {        
        perror("Unable to execute command:");        
        printf("  command:   %s\n", command);        
        printf("  exit code: %d\n", exitCode);    
    } 
}
