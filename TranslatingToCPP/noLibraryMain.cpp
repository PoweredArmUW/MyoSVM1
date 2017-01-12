#include <cmath>
#include <iostream>
#include <array>

using namespace std;

//load array into arr;
double arr[3][8]; //arbitrary array
int arrRow = 3;

double train[arrRow][8];
double label[arrRow];
for (int i = 0; i < arrRow; i++)
{
    for (int j = 0; j<8; j++)
    {
        train[i][j] = arr[i][j];
    }
    label[i] = arr[i][8];
}

int freq = 200;
double mincutoff = 0.8, beta = 0.4, dcutoff = 1.0;
double duration = 1.0;

f=  OneEuroFilter(freq,mincutoff,beta,dcutoff);
double timestamp = 20;
//this wont run??
while (timestamp < duration)
{
    double filtered = f.filter(train, timestamp);  //does it take a array value??
    timestamp += 1.0/freq;
}
