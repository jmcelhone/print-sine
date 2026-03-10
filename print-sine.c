#include <math.h>
#include <stdio.h>

int main(void) {
	double angle = 0;

	while (angle <= 2 * M_PI) {
		printf("%.2lf\n", sin(angle));
		angle += 0.1;
	}
}

