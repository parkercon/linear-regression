#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <iostream>
using namespace std;

class Matrix{
    private: 
        vector<vector<float> > values;
        int rows;
        int columns;
        int length;

    public:
        Matrix();
        ~Matrix();
        Matrix& operator=(const Matrix&);
     
        vector<vector<float> > get_values();
        int get_rows();
        int get_columns();
        int get_length();

        void print();

        void set_values(vector<float>);
        void set_rows(int);
        void set_columns(int);
        void set_length(int);


};

#endif