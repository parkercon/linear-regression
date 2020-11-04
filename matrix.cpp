#include "matrix.h"

Matrix::Matrix(){
    this->length = 0;
    this->rows = 0;
    this->columns = 0;
}

Matrix::~Matrix(){

}

Matrix& Matrix::operator=(const Matrix& old_obj){
    cout << "\nCOPY\n";
    if (this != &old_obj){
        this->rows = old_obj.rows;
        this->columns = old_obj.columns;
        this->length = old_obj.length;
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->columns; j++)
            {
                this->values[i][j] = old_obj.values[i][j];
            }
        }
    }
    return *this;
}

vector<vector<float> > Matrix::get_values(){
    return this->values;
}

int Matrix::get_rows(){
    return this->rows;
}

int Matrix::get_columns(){
    return this->columns;
}

int Matrix::get_length(){
    return this->length;
}

void Matrix::set_values(vector<float> row){
    this->values.push_back(row);
    this->rows++;
    this->length++;
}

void Matrix::set_rows(int r){
    this->rows = r;
}
void Matrix::set_columns(int cols){
    this->columns = cols;
}



void Matrix::print(){
    for (int i = 0; i < this->rows; i++){
        for (int j = 0; j < this->columns; j++){
            cout << this->values[i][j] << " ";
        }
        cout << endl;
    }
}

