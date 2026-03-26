#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <time.h>

int main(int argc, char *argv[]) {
	struct winsize w;

	if (argc != 3) {
		fprintf(stderr, "Usage: ./print-sine height frequency");
		return 1;
	}

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w)) {
		perror("Error getting window width");
		return 1;
	}

	const int height = atoi(argv[1]);
	const double frequency = strtod(argv[2], NULL);
	const double step = 2.0 / height;

	const int width = w.ws_col;
	double angle = 0;
	double *sine_arr = (double *)malloc(width * sizeof(double)); 
	int head = 0;

	// Initalize angle values
	for (int i = 0; i < width; i++) {
		sine_arr[i] = sin(angle);
		angle += frequency;
	}

	// Timer stuff
	struct timespec interval = {0, 30000000};
	
	while (1) {
		// Clear screen
		nanosleep(&interval, &interval);
		printf("\e[1;1H\e[2J");

		// Draw loop
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				if (sine_arr[(head + j) % width] >= -1.0 + i * step && sine_arr[(head + j) % width] < -1 + (i + 1) * step) {
					printf("*");
				} else {
					printf(" ");
				}
			}
			printf("\n");
		}

		// Process loop
		angle += frequency;
		sine_arr[head] = sin(angle);
		head = (head + 1) % width;
	}
	
	free(sine_arr);
}
