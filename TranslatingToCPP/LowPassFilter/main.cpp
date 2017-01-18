#include <stdio.h>
#include <math.h>
#include "graphFunc.h"
#include "LowPassFilter.h"
#include "OneEuroFilter.h"
#include <cmath>

// Overwrite first n elements of 'data' with a lowlass filtered version of its values.
void low_pass(float data[], int n, float alpha) {

	for (int i = 1; i<n; i++) {
		data[i] = alpha*(data[i]-data[i-1]) + data[i-1];
	}
}

double generateAlpha(double freq = 200, double mincutoff = 0.8, double beta = 0.4)
{
    double te = 1.0/freq;
    double tau = 1.0/(2*M_PI*mincutoff);
    return (1.0/(1.0 + tau/te));
}

int main(int argc, char* argv[]) {
	int num_trials = 60;
	float gains1[num_trials];
	float gains2[num_trials];
	float filtered[num_trials];
	OneEuroFilter oef(200, 0.8, 0.4, 1.0);
	LowPassFilter lpf(generateAlpha());

    for (int i=0; i<num_trials; i++) {
        int num_samples = 800;
        float data[num_samples];
        float filtered[num_samples];
        for (int j = 0; j < num_samples; j++)
        {
            data[j] = sin((i/80.0)*j);
            filtered[j] = oef.filter(data[j]);
        }
        gains1[i] = range(data, num_samples)/2;
        gains2[i] = range(filtered, num_samples)/2;
    }
    // Graph Function
    printf("Unfiltered\n\n");
    graph(gains1, num_trials);
    printf("\n\n");

    printf("Filtered\n\n");
    graph(gains2, num_trials);
    printf("\n");

	return 0;
}
