#include "task.h"

using namespace task2;

void task2::main_task2() {
    //point_1();
    vector<double> coef = get_coef();
    task1::point_2_3("line_task2.txt",coef);
    system("python D:\\5sem\\numerical\\practice\\Lab3\\src\\plot\\task2.py");
}

void task2::point_1() {
    int n = get_n();
    vector<vector<double>> A = set_matrix(n), A_print;
    A_print = A;
    vector<double> d = set_vector(n), x;
    set_system(A_print, d);
    vector<vector<double>> L(n, vector<double>(n, 0)), U(n, vector<double>(n, 0));
    LU(A, L, U, n);
    cout << "L:\n";
    print_matrix(L,1);
    cout << "U:\n";
    print_matrix(L,1);
    x = solution_LU(L, U, d);
    cout << "Решение системы: \n";
    print_vector(x, 1);
}


void task2::LU(vector<vector<double>> A, vector<vector<double>> &L,
               vector<vector<double>> &U, int n) {
    U = A;

    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            L[j][i] = U[j][i] / U[i][i];

    for (int k = 1; k < n; k++) {
        for (int i = k - 1; i < n; i++)
            for (int j = i; j < n; j++)
                L[j][i] = U[j][i] / U[i][i];

        for (int i = k; i < n; i++)
            for (int j = k - 1; j < n; j++)
                U[i][j] = U[i][j] - L[i][k - 1] * U[k - 1][j];
    }

}

vector<double> task2::solution_LU(vector<vector<double>> &L, vector<vector<double>> &U, vector<double> &d) {
    int n = L.size();
    vector<double> x(n, 0), y(n, 0);

    y[0] = d[0] / L[0][0];
    for (int i = 1; i <= n - 1; i++) {
        y[i] = d[i] / L[i][i];
        for (int j = 0; j < i; j++) {
            y[i] -= ((L[i][j] * y[j]) / L[i][i]);
        }
    }

    x[n - 1] = y[n - 1] / U[n - 1][n - 1];
    for (int i = n - 2; i >= 0; i--) {
        x[i] = y[i] / U[i][i];
        int raz = abs(i - n + 1);
        for (int j = 1; j <= raz; j++) {
            x[i] -= ((U[i][i + j] * x[i + j]) / U[i][i]);
        }
    }
    return x;
}


vector<vector<double>> set_rand_matrix(int n) {
    srand(time(0));
    vector<vector<double>> matrix(n, vector<double>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = -10 + rand() % 20;
        }
    }
    return matrix;
}

vector<double> set_rand_vector(int n) {
    vector<double> d(n);
    srand(time(0));
    for (int i = 0; i < n; i++) {
        d[i] = -10 + rand() % 20;
    }
    return d;
}

vector<double> task2::get_coef() {
    vector<vector<double>> Matrix(6),L(6, vector<double>(6, 0)), U(6, vector<double>(6, 0)),Matrix_print;
    vector<double> d;
    for (int i = 0; i < x.size(); i++) {
        Matrix[i].push_back(1);// a0
        Matrix[i].push_back(x[i]);// a1 * x
        Matrix[i].push_back(-x[i] * y[i]); // -b1 * x * y
        Matrix[i].push_back(-x[i] * x[i] * y[i]);// -b2 * x (^2) * y
        Matrix[i].push_back(-x[i] * x[i] * x[i] * y[i]);// -b3 * x(^3) * y
        Matrix[i].push_back(-x[i] * x[i] * x[i] * x[i] * y[i]);// -b4 * x(^4) * y
        d.push_back(y[i]); // = yi
    }
    cout << "Исходная матрица:\n";
    Matrix_print=Matrix;
    set_system(Matrix_print,d);
    print_matrix(Matrix_print,1);
    LU(Matrix,L,U,6);
    cout << "L:\n";
    print_matrix(L,1);
    cout << "U:\n";
    print_matrix(U,1);
    vector<double> coef= solution_LU(L,U,d);
    cout << "Решение системы:\n";
    print_vector(coef,1);
    return coef;
}

