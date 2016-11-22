#ifndef DATAREADER_H
#define DATAREADER_H

#include <string>
using namespace std;

class DataArray{
private:
    float* array;
    int _cols;
    int _rows;
public:
    DataArray(int, int);
    ~DataArray();
    float& index(int, int);
    int rows();
    int cols();
};

DataArray* readData(string filename);

#endif