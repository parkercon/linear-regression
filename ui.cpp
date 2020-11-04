/*===================================
 * Author: Parker Conrad
 * Email: parkerconrad814@yahoo.com
===================================*/

#include <matplot/matplot.h> 
#include "ui.h"
#include "matrix.h"
#include "linear_regression.h"
#include<iostream>
using namespace std;

Ui::Ui(){

}

Ui::~Ui(){

}

void Ui::load_interface(){
    Linear_regression lr_functions;
    string text_file;
    char input;
    Matrix* x_values = new Matrix; // need to delete
    Matrix* y_values = new Matrix; // need to delete
    
    cout << "Please enter the name of the txt file with the data\n";
    cin >> text_file;
    ifstream data(text_file); // error handle

    cout << "\nReading Data...\n";
    lr_functions.read_data(data, x_values, y_values);

    vector <double> plot_x, plot_y;
    vector <vector<float> > x_tmp = x_values->get_values();
    vector <vector<float> > y_tmp = y_values->get_values();
    vector <double> plot_t;
    float* tmp_t2;

    cout << "Printing X values: (columns of 1 added to allow for matrix operations)\n";
    x_values->print();
    cout << "Printing Y values: \n";
    y_values->print();
cout << "Printing Transpose of X: \n";
lr_functions.transpose(x_values);
    do {
        float alpha = lr_functions.get_alpha();
        float iterations = lr_functions.get_iterations();
        float* theta = lr_functions.get_theta();
        cout<< "\nHello,\nWelcome to the Linear Regression Calculator\n"
            << "Alpha: " << alpha
            << "\nIterations: " << iterations
            << "\nTheta: " << endl << theta[0] << endl << theta[1] << endl;

        cout << "\nWhat would you like to do\n"
            << "1. Set Alpha (learning rate for gradient descent)\n"
            << "2. Set Theta (function hypothesis)\n"
            << "3. Set iterations (gradient steps)\n"
            << "4. Compute Cost function\n"
            << "5. Compute Gradient Descent to optimize theta\n"
            << "6. Plot graph with linear regression\n"
            << "7. Quit\n";
            cin >> input;

       if (input == '1') {
            float alpha;
            cout << "\nWhat would you like alpha to be?:\n";
            cin >> alpha;
            lr_functions.set_alpha(alpha);
        
       }

        else if (input == '2') {
            float theta[2];
            cout << "Theta[1]: \n";
            cin >> theta[0];
            cout << "Theta[2]: \n";
            cin >> theta[1];
            lr_functions.set_theta(theta);
        
        }

        else if (input == '3') {
            int iterations;
            cout << "What wuld you like the iterations to be:\n";
            cin >> iterations;
            lr_functions.set_iterations(iterations);
        }

        else if (input == '4') {
            lr_functions.compute_cost(x_values, y_values, lr_functions.get_theta());
        }

        else if (input == '5') { 
            tmp_t2 = lr_functions.gradient_descent(x_values, y_values, lr_functions.get_theta(), lr_functions.get_alpha(), lr_functions.get_iterations());
        }

        else if (input == '6') {
            for (int i = 0; i < x_values->get_rows(); i++)
            {
                plot_x.push_back(x_tmp[i][1]);
                plot_y.push_back(y_tmp[i][0]);
            }
            float* tmp_theta = tmp_t2;
            Matrix* tmp =  lr_functions.multiply(x_values, y_values, tmp_theta, true);
            vector<vector<float> > t = tmp->get_values();
            for (int i = 0; i < x_values->get_rows(); i++)
            {
                plot_t.push_back(t[i][0]);
            }
            

        matplot::scatter(plot_x, plot_y);
        matplot::hold(true);
        matplot::plot(plot_x, plot_t);

        }
            
        else if (input == '7') {
            delete x_values;
            delete y_values;
            return;
        }
        
        else{
            cout << "Invalid input, try again\n";
            break;
        }
    }
    while (input != '7');

}
