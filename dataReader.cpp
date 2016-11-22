#include <fstream>
#include "dataReader.h"
using namespace std;

DataArray::DataArray(int r, int c){
        _cols = c;
        _rows = r;
        array = new float[_rows*_cols];
    }

DataArray::~DataArray(){
        delete[] array;
    }

float& DataArray::index(int x, int y){
        return array[x*_cols+y];
    }

int DataArray::rows (){
        return _rows;
    }
int DataArray::cols (){
        return _cols;
    }

DataArray* readData(string filename){
    ifstream csvfile;

    csvfile.open(filename);
    if (csvfile.fail()){
        return NULL;
    }

    const int maxLineSize = 1000;
    char line[maxLineSize];
    string word;
    int rows;
    int columns;

    csvfile.getline(line, maxLineSize);
    int i = 0;
    while (line[i] != 0){
        if (line[i] != ','){
            word.push_back(line[i]);
        }
        else{
            rows = stoi(word);
            word.clear();
        }
        i++;
    }
    columns = stoi(word);
    word.clear();

    DataArray *array = new DataArray(rows, columns);
    int curRow = 0;
    while (csvfile.getline(line, maxLineSize)){
        int curCol = 0;
        int i = 0;
        while (line[i] != 0){
            if (line[i] != ','){
                word.push_back(line[i]);
            }
            else{
                array->index(curRow,curCol) = stof(word);
                word.clear();
                curCol++;
            }
            i++;
        }
        array->index(curRow,curCol) = stof(word);
        word.clear();
        curRow++;
    }
    csvfile.close();
    return array;
}