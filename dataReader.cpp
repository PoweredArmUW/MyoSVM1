#include <fstream>
#include <string>
#include <iostream>
using namespace std;

class DataArray{
    private:
    float* array;
    int columns;
    int rows;

    public:
    DataArray(int r, int c){
        columns = c;
        rows = r;
        array = new float[rows*columns];
    }

    ~DataArray(){
        delete[] array;
    }

    float& index(int x, int y){
        return array[x*columns+y];
    }

    int rowCount (){
        return rows;
    }
    int colCount (){
        return columns;
    }
};

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
    cout << curRow << endl;
    return array;
}