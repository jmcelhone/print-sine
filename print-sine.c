#include <math.h>
#include <stdio.h>

int main(void) {
	double angle = 0;
	double angle_arr[63] = {0}; 

	int i = 0;
	while (angle <= 2 * M_PI) {
		angle_arr[i] = sin(angle);
		angle += 0.1;
		i++;
	}
	
	for (int i = 0; i < 63; i++) {
		printf("%.2lf\n", angle_arr[i]);
	}
}

