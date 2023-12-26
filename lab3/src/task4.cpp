#include "task.h"

using namespace task4;

void task4::main_task4() {
    int n = 10;
    vector<vector<double>> M(n, vector<double>(n, 0)), M_print;
    vector<double> b;
    set_rand_value(n, M, b);

    cout << "Система:\n";
    M_print = M;
    set_system(M_print, b);
    print_matrix(M_print, 1);

    vector<double> ANS = FifthDiag(M, b);
    cout << "Решение системы:\n";
    print_vector(ANS, 1);

    vector<double> check = check_get_vector(n, M, ANS);
    cout << "Сгенерованный вектор:\n";
    print_vector(check, 1);
    cout << "Вектор ответов:\n";
    print_vector(b, 1);

}

vector<double> task4::check_get_vector(int n, const vector<vector<double>> &M, const vector<double> &ANS) {
    vector<double> check(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            check[i] += ANS[j] * M[i][j];
        }
    }
    return check;
}

void task4::set_rand_value(int n, vector<vector<double>> &M, vector<double> &b) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        b.push_back(rand() % 10);
    }
    int j = 2;
    for (int i = 2; i < n - 2; i++, j++) {
        M[i][j - 2] = rand() % 10;
        M[i][j - 1] = rand() % 10;
        M[i][j] = rand() % 10;
        M[i][j + 1] = rand() % 10;
        M[i][j + 2] = rand() % 10;
    }
    j = 0;
    for (int i = 0; i < 2; i++, j++) {
        if (i == 0) {
            // row 1
            M[i][j] = rand() % 10;
            M[i][j + 1] = rand() % 10;
            M[i][j + 2] = rand() % 10;
            // row n
            M[n - 1][n - 3] = rand() % 10;
            M[n - 1][n - 2] = rand() % 10;
            M[n - 1][n - 1] = rand() % 10;
        } else if (i == 1) {
            //row 2
            M[i][j - 1] = rand() % 10;
            M[i][j] = rand() % 10;
            M[i][j + 1] = rand() % 10;
            M[i][j + 2] = rand() % 10;
            //row n-1
            M[n - 2][n - 4] = rand() % 10;
            M[n - 2][n - 3] = rand() % 10;
            M[n - 2][n - 2] = rand() % 10;
            M[n - 2][n - 1] = rand() % 10;
        }
    }
}


vector<double> task4::FifthDiag(vector<vector<double>> &M, vector<double> &ansvec) {
    int n = M.size();
    vector<double> a(n), b(n), c(n), d(n), e(n), alpha(n), betta(n), gamma(n), X(n);
    a[0] = 0;
    b[0] = 0;
    a[1] = 0;
    e[n - 1] = 0;
    d[n - 1] = 0;
    //1 rows
    c[0] = M[0][0];
    d[0] = M[0][1];
    e[0] = M[0][2];
    //2 rows
    b[1] = M[1][0];
    c[1] = M[1][1];
    d[1] = M[1][2];
    e[1] = M[1][3];
    //3-n-2 rows
    int j = 0;
    for (int i = 2; i < n - 2; i++, j++) {
        a[i] = M[i][j];
        b[i] = M[i][j + 1];
        c[i] = M[i][j + 2];
        d[i] = M[i][j + 3];
        e[i] = M[i][j + 4];
    }
    //n-2 rows
    a[n - 2] = M[n - 2][n - 4];
    b[n - 2] = M[n - 2][n - 3];
    c[n - 2] = M[n - 2][n - 2];
    d[n - 2] = M[n - 2][n - 1];
    //n-1 line
    a[n - 1] = M[n - 1][n - 3];
    b[n - 1] = M[n - 1][n - 2];
    c[n - 1] = M[n - 1][n - 1];

    alpha[0] = -d[0] / c[0];
    betta[0] = -e[0] / c[0];

    gamma[0] = ansvec[0] / c[0];

    alpha[1] = -(b[1] * betta[0] + d[1]) / (c[1] + b[1] * alpha[0]);
    betta[1] = -e[1] / (c[1] + b[1] * alpha[0]);
    gamma[1] = (ansvec[1] - b[1] * gamma[0]) / (c[1] + b[1] * alpha[0]);

    double delitel = 0;
    double d1 = 0;
    double d2 = 0;
    double d3 = 0;

    for (int i = 2; i < n; i++) {
        delitel = ((betta[i - 2] + alpha[i - 1] * alpha[i - 2]) * a[i] + alpha[i - 1] * b[i] + c[i]);

        d1 = (a[i] * alpha[i - 2] * betta[i - 1] + b[i] * betta[i - 1] + d[i]);
        d2 = (e[i]);
        d3 = (ansvec[i] - (a[i] * alpha[i - 2] * gamma[i - 1] + a[i] * gamma[i - 2] + b[i] * gamma[i - 1]));
        alpha[i] =
                -d1
                /
                delitel;
        betta[i] =
                -d2
                /
                delitel;
        gamma[i] =
                d3
                /
                delitel;
    }
    X[n - 1] = gamma[n - 1];
    X[n - 2] = alpha[n - 2] * X[n - 1] + gamma[n - 2];

    for (int i = n - 3; i >= 0; i--) {
        X[i] = betta[i] * X[i + 2] + alpha[i] * X[i + 1] + gamma[i];
    }
    return X;
}