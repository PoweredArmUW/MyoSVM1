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
    DataArray(DataArray&, bool);
    DataArray(string filename);
    ~DataArray();
    float& index(int, int);
    int rows();
    int cols();
};

#endif