#ifndef GRAPHFUNC_H
#define GRAPHFUNC_H
#include <stdio.h>
#include <math.h>
void graph(float data[], int n)
{
	float height = 20;

	float max = -1000000000, min = 1000000000;
	// Find max and min vals
	for (int i=0; i<n; i++) {
		if (data[i] > max) max = data[i];
		if (data[i] < min) min = data[i];
	}
	if (max < min) {
		printf("Data out of range");
	}
	float range = (max - min);

	for (int i=(int)height; i>0; i--) {
		printf("%.2f\t",min+(i-0.5)*range/height);
		for (int j=0; j<n; j++) {
			if (data[j] <= min+i*range/height && data[j] > min+(i-1)*range/height) {
				printf("*");
			} else if (0 <= min+i*range/height && 0 >= min+(i-1)*range/height) {
				printf("-");
			} else {
				printf(" ");
			}
		} printf("\n");
	}
}

float range(float data[], int n) {
	// Graph is 12 bars high peak to peak, and 80 chars long (at max)
	float max = -1000000000, min = 1000000000;
	// Find max and min vals
	for (int i=0; i<n; i++) {
		if (data[i] > max) max = data[i];
		if (data[i] < min) min = data[i];
	}
	return (max - min);
}
#endif // GRAPHFUNC_H

