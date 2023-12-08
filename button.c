#include "button.h"

//function to get value of a GPIO file
int getUSERvalue(){
    FILE *file = fopen(USER_BUTTON_VALUE, "r");
    if (file == NULL){
        printf("Error opening file %s\n", USER_BUTTON_VALUE);
        exit(1);
    }
    int value = fgetc(file);
    fclose(file);
    return value;
}

//function to write to file
void writetoFile(const char* value){
	FILE *pFile = fopen(USER_BUTTON_DIRECTION, "w");
    if (pFile == NULL) {
        printf("ERROR: Unable to open file %s.\n", USER_BUTTON_DIRECTION);
        exit(1);
    }
	fprintf(pFile, "%s", value);
	fclose(pFile);
}
