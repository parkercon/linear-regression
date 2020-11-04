#include "linear_regression.h"
#include <iostream>
using namespace std;

Linear_regression::Linear_regression(){
    this->alpha = 0.01;
    this->iterations = 1500;
    this->theta = new float [2];
    this->theta[0] = 0;
    this->theta[1] = 0;
}

Linear_regression::~Linear_regression(){
    delete [] this->theta;
    this->theta = NULL;
 
}

int Linear_regression::get_iterations(){
    return this->iterations;
}

float Linear_regression::get_alpha(){
    return this->alpha;
}

float* Linear_regression::get_theta(){
    return theta;
}

void Linear_regression::set_alpha(float a){
    this->alpha = a;
}

void Linear_regression::set_theta(float* t){
    this->theta[0] = t[0];
    this->theta[1] = t[1];
}

void Linear_regression::set_iterations(int i){
    this->iterations = i;
}


void Linear_regression::read_data(ifstream &data, Matrix* x_values, Matrix* y_values){

    float x;
    float y;
    string skip;

    int i = 0;
    int j =0;
    vector<float> x_row;
    vector<float> y_row;

    x_values->set_columns(2);
    y_values->set_columns(1);
    while (data >> x && getline(data, skip, ',') && data >> y)
    {
        x_row.push_back(1);
        i++;
        x_row.push_back(x);
        i++;
        y_row.push_back(y);
        j++;
        x_values->set_values(x_row);
        y_values->set_values(y_row);
        if (i == 2){
            i = 0;
            x_row.clear();
        }
        if (j == 1){
            j = 0;
            y_row.clear();
        }
    }
} 

Matrix* Linear_regression::multiply(Matrix* x, Matrix* y, float* theta, bool vector_input){
    Matrix* product = new Matrix;
    vector<vector<float> > x_temp = x->get_values();
    vector<vector<float> > y_temp = y->get_values();
    vector<float> product_temp;

    if (vector_input == true) {
        product->set_columns(1);
        for (int i = 0; i < x->get_rows(); i++)
        {
            product_temp.push_back((x_temp[i][0] * theta[0]) + (x_temp[i][1] * theta[1]));
            product->set_values(product_temp);
            product_temp.clear();
        }
        return product;
    }
    else if(vector_input == false){
        vector<vector<float> > temp_row(2, vector<float>(1));
        product->set_columns(y->get_columns());
        for (int i = 0; i < x->get_columns(); i++)
        {
            temp_row[0][0] += x_temp[0][i] * y_temp[i][0];
        }
        product->set_values(temp_row[0]);
        for (int i = 0; i < x->get_columns(); i++)
        {
            temp_row[1][0] += x_temp[1][i] * y_temp[i][0];
        }
        product->set_values(temp_row[1]);
        
        return product;
    }
    delete product;
    product = NULL;
}

Matrix* Linear_regression::subtract(Matrix* x, Matrix* y){
    Matrix* product = new Matrix;
    product->set_columns(1);
    vector<vector<float> > x_temp = x->get_values();
    vector<vector<float> > y_temp = y->get_values();
    vector<float> product_temp; 

    for (int i = 0; i < x->get_rows(); i++)
    {
        product_temp.push_back(x_temp[i][0] - y_temp[i][0]);
        product->set_values(product_temp);
        product_temp.clear();
    }

    return product;
    delete product;
    product = NULL;
}

Matrix* Linear_regression::square(Matrix* x){
    Matrix* product = new Matrix;
    product->set_columns(1);
    vector<vector<float> > x_temp = x->get_values();
    vector<float> product_temp;
    for (int i = 0; i < x->get_rows(); i++)
    {
        product_temp.push_back(x_temp[i][0] * x_temp[i][0]);
        product->set_values(product_temp);
        product_temp.clear();
    }
    
    return product;
    delete product;
    product = NULL;
}

float Linear_regression::sum(Matrix* x){
    float matrix_sum = 0;
    vector<vector<float> > x_temp = x->get_values();
    for (int i = 0; i < x->get_rows(); i++)
    {
        matrix_sum += x_temp[i][0];
    }
    return matrix_sum;
}

Matrix* Linear_regression::transpose(Matrix* x){
    int c = x->get_columns();
    int r = x->get_rows();
    vector<vector<float> > x_copy = x->get_values();
    vector<float> tmp_row;
    Matrix* tran_x = new Matrix;
    for (int i = 0; i < c; i++)
    {
        for (int j = 0; j < r; j++)
        {
            tmp_row.push_back(x_copy[j][i]);
        }
        tran_x->set_values(tmp_row);   
        tmp_row.clear();

    }
    tran_x->set_columns(r);
    tran_x->print();
    return tran_x;  
}

float Linear_regression::compute_cost(Matrix* x, Matrix* y, float* theta)
{
    int m = y->get_length();
    float s = sum(square((subtract(multiply(x, y, theta, false), y))));
    cout << "S: " << s << endl;
    float answer = s / (2 * m);

    cout << "MINIMIZED COST: " << answer << endl;

    return answer;

}

float* Linear_regression::gradient_descent(Matrix* x, Matrix* y, float* theta, float alpha, int iterations){
    int m = y->get_length();
    Matrix* x_trans_temp = transpose(x);
    vector<vector<float> > product3;
    for (int i = 0; i < iterations; i++)
    {
        vector<vector<float> > x_trans = x_trans_temp->get_values();
        Matrix* product = new Matrix;
        Matrix* product2 = new Matrix;
        product = multiply(x, y, theta, true);
        product = subtract(product, y);
        product2->set_columns(x->get_rows());
       for (int j = 0; j < x_trans_temp->get_length(); j++)
       {
           for (int k = 0; k < x_trans_temp->get_columns(); k++)
           {
               x_trans[j][k] *= (alpha/m);
           }
           product2->set_values(x_trans[j]);
       }

       product2 = multiply(product2, product, theta, false);
       product3 = product2->get_values();
       theta[0] = theta[0] - product3[0][0];
       theta[1] = theta[1] - product3[1][0];
        delete product;
        product = NULL;
        delete product2;
        product2 = NULL;
    }
    return theta;

    
}