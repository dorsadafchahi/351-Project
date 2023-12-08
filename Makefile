# Define the common flags and compiler
CC = arm-linux-gnueabihf-gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror -Wno-unused-variable

# Target for light_sampler
light_sampler: main.c waterSampling.c LEDmatrix.c time.c gpio.c lcd.c button.c joystick.c
	$(CC) $(CFLAGS) main.c waterSampling.c LEDmatrix.c time.c gpio.c lcd.c button.c joystick.c -o main -lpthread
	cp main ~/ensc351/public/myApps/

.PHONY: all clean

all: main

clean:
	rm -f main
