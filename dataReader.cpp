#include <fstream>
#include "dataReader.h"
using namespace std;

DataArray::DataArray(){
    _cols = 0;
    _rows = 0;
    array = new float [0];
}

DataArray::DataArray(int r, int c){
        _cols = c;
        _rows = r;
        array = new float[_rows*_cols];
    }

DataArray::DataArray(DataArray& orig, bool transpose){
    if (transpose){
        _cols = orig.rows();
        _rows = orig.cols();
    }
    else{
        _rows = orig.rows();
        _cols = orig.cols();
    }
    array = new float[_rows*_cols];
    for (int i=0; i<orig.rows(); i++){
        for (int j=0; j<orig.cols(); j++){
            if (transpose){
                this->index(j,i) = orig.index(i,j);
            }
            else{
                this->index(i,j) = orig.index(i,j);
            }
        }
    }
}

DataArray::~DataArray(){
    _cols = _rows = -1;
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

DataArray::DataArray(string filename){
    ifstream csvfile;

    csvfile.open(filename);
    if (csvfile.fail()){
        _rows = 0;
        _cols = 0;
        array = NULL;
        return;
    }

    const int maxLineSize = 1000;
    char line[maxLineSize];
    string word;

    csvfile.getline(line, maxLineSize);
    int i = 0;
    while (line[i] != 0){
        if (line[i] != ','){
            word.push_back(line[i]);
        }
        else{
            _rows = stoi(word);
            word.clear();
        }
        i++;
    }
    _cols = stoi(word);
    word.clear();

    array = new float[_rows*_cols];
    int curRow = 0;
    while (csvfile.getline(line, maxLineSize)){
        int curCol = 0;
        int i = 0;
        while (line[i] != 0){
            if (line[i] != ','){
                word.push_back(line[i]);
            }
            else{
                this->index(curRow,curCol) = stof(word);
                word.clear();
                curCol++;
            }
            i++;
        }
        this->index(curRow,curCol) = stof(word);
        word.clear();
        curRow++;
    }
    csvfile.close();
}

DataArray& DataArray::operator=(DataArray& orig){
    _rows = orig.rows();
    _cols = orig.cols();
    delete[] array;
    array = new float[_rows*_cols];
    for (int i=0; i<orig.rows(); i++){
        for (int j=0; j<orig.cols(); j++){
            this->index(i,j) = orig.index(i,j);
        }
    }
    return *this;
}