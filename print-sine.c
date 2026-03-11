#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

int main(int argc, char *argv[]) {
	struct winsize w;

	if (argc != 3) {
		fprintf(stderr, "Usage: ./print-sine height frequency");
		return 1;
	}

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w)) {
		perror("Error getting window size");
		return 1;
	}

	const int height = atoi(argv[1]);
	const double frequency = strtod(argv[2], NULL);
	const double step = 2.0 / height;

	const int width = w.ws_col;
	double angle = 0;
	double *angle_arr = (double *)malloc(width * sizeof(double)); 

	for (int i = 0; i < width; i++) {
		angle_arr[i] = sin(angle);
		angle += frequency;
	}
	
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			if (angle_arr[j] >= -1.0 + i * step && angle_arr[j] < -1 + (i + 1) * step) {
				printf("*");
			} else {
				printf(" ");
			}
		}
		printf("\n");
	}
	
	free(angle_arr);
}
