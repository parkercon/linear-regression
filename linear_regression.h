#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H
#include "matrix.h"
#include <fstream>
#include <vector>
using namespace std;

class Linear_regression{
    private:
        int iterations;
        float alpha;
        float* theta;

    public: 
        Linear_regression();
        ~Linear_regression();
        int get_iterations();
        float get_alpha();
        float* get_theta();

        void set_alpha(float);
        void set_theta(float*);
        void set_iterations(int);

        
        Matrix* transpose(Matrix*);
        Matrix* multiply(Matrix*, Matrix*, float*, bool);
        Matrix* subtract(Matrix*, Matrix*);
        Matrix* square(Matrix*);
        float sum(Matrix* x);
        float* gradient_descent(Matrix*, Matrix*, float*, float, int);
        float compute_cost(Matrix*, Matrix*, float*);
        void read_data(ifstream&, Matrix*, Matrix*);
};

#endif