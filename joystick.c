#include "joystick.h"

infoSens *sVal;

double Joystick_readX() {
	FILE *voltage_file = fopen(JoyX, "r");
	if (!voltage_file) {
		printf("ERROR: Unable to open voltage input file\n");
		exit(-1);
	}
	int value = 0;
	fscanf(voltage_file, "%d", &value);
	fclose(voltage_file);
    double val = value;
	return val;
}

double Joystick_readY() {
	FILE *voltage_file = fopen(JoyY, "r");
	if (!voltage_file) {
		printf("ERROR: Unable to open voltage input file\n");
		exit(-1);
	}
	int value = 0;
	fscanf(voltage_file, "%d", &value);
	fclose(voltage_file);
    double val = value;
	return val;
}

int getDirection(){
	double Xval = Joystick_readX();
	double Yval = Joystick_readY();
	if(Xval > Yval && Xval >= (double)3700){
		return 1; //Left 
	}
	else if((Xval < Yval && Xval <= (double)1100) || Xval == (double)0){
		return 2; //Right
	}
	else if(Yval > Xval && Yval >= (double)3700){
		return 3; //Up
	}
	else if((Yval < Xval && Yval <= (double)1100) || Yval == (double)0){
		return 4; //Down
	}
	return 0;
}

void joystickInfo(infoSens *sVal) {
	char result[60] = "";
    char result2[17] = "";
	int joystick_dir = getDirection();
    switch (joystick_dir)
    {
		case 0: // nothing
			snprintf(result, sizeof(result), "Blue:%2d%c Blk:%2d%c                        ", sVal->infoPerc2, '%', sVal->infoPerc1, '%');
            if (sVal->infoPerc2 == sVal->infoPerc1) {
                snprintf(result2, sizeof(result2), "Percentage equal");
            } else if (sVal->infoPerc2 < sVal->infoPerc1) {
                snprintf(result2, sizeof(result2), "Blue is cleaner ");
            } else {
                snprintf(result2, sizeof(result2), "Black is cleaner");
            }
            strcat(result, result2);
            writeMessage(result);
			sleepForMs(750);
			break;
		case 1: // right
			snprintf(result, sizeof(result), "Blck sensor: %2d%c                        Avg: %7.2f", sVal->infoPerc1, '%', sVal->infoAvg1);
            writeMessage(result);
			sleepForMs(1000);
			break;
		case 2: // left
			snprintf(result, sizeof(result), "Blue sensor: %2d%c                        Avg: %7.2f", sVal->infoPerc2, '%', sVal->infoAvg2);
			writeMessage(result);
			sleepForMs(1000);
			break;
		case 3: // up
			writeMessage("Higher percent =                        Water from hell!");
			sleepForMs(3000);
			break;
		case 4: // down
			writeMessage("Hold USER to                            re-analyze...");
			sleepForMs(2000);
			break;
    }
}