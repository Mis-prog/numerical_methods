#include <iostream>
#include <vector>
#include <windows.h>
#include <iomanip>
#include <fstream>
#include <random>
#include <math.h>

void Task3();

using namespace std;

void print_matrix(vector<vector<double>> A, bool type);

void print_vector(vector<double> A, bool type);

vector<vector<double>> set_rand_matrix(int n);

vector<double> set_rand_vector(int n);

vector<vector<double>> set_matrix(int n);

void set_system(vector<vector<double>> &matrix_coef, vector<double> &d);

vector<double> set_vector(int n);

int get_n();

const vector<double> x = {-3.5, -2.1, -0.7, 0.7, 2.1, 3.5};

const vector<double> y = {-2.0709, -0.73400, -0.60998, 0.34831, 0.28276, 0.16644};

namespace task1 {
    vector<double> method_gaussa(vector<vector<double>> matrix_coef);

    void main_task1();

    vector<double> get_coef();

    void point_1();

    double rational_interpoletion(vector<double> &coef, double x);

    void write_node_file();

    void point_2_3(char *name, vector<double> &coef);
}

namespace task2 {
    void main_task2();

    void point_1();

    void LU(vector<vector<double>> A, vector<vector<double>> &L, vector<vector<double>> &U, int n);

    vector<double> solution_LU(vector<vector<double>> &L, vector<vector<double>> &U, vector<double> &d);

    vector<double> get_coef();
}


namespace task4 {
    const int N = 9;

    void main_task4();

    vector<double> FifthDiag(vector<vector<double>>& M, vector<double>& ansvec);

    void set_rand_value(int n, vector<vector<double>> &M, vector<double> &b);

    vector<double> check_get_vector(int n, const vector<vector<double>> &M, const vector<double> &ANS);
}