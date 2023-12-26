#include <stdio.h>
#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include <time.h>
#include <vector>
#include <windows.h>
#include <cmath>
#include <iomanip>

#include "Methods.h"

const int N = 750;
const int l = 34;

void PrintMatrix(vector<vector<double>> Matrix)
{
    cout << fixed << std::setprecision(4);
    cout << "-------------------------------------------------------------" << endl;
    for (int i = 0; i < Matrix.size(); i++)
    {
        for (int j = 0; j < Matrix[i].size(); j++)
        {
            cout << setw(5) << Matrix[i][j] << "  ";
        }
        cout << endl;
    }
    cout << "-------------------------------------------------------------" << endl;
}
void PrintVector(vector<double> Vector)
{
    cout << fixed << std::setprecision(4);
    cout << "-------------------------------------------------------------" << endl;
    for (int i = 0; i < Vector.size(); i++)
    {
        cout << setw(5) << Vector[i] << " ";
    }

    cout << endl <<  "-------------------------------------------------------------" << endl;
}


void
task2(double q1, double q2, double q3, vector<double> &sol, vector<double> &b1, vector<double> &b2, vector<double> &b3,
      vector<double> &x1, vector<double> &x2, vector<double> &x3, vector<vector<double>> &Lenta1,
      vector<vector<double>> &Lenta2, vector<vector<double>> &Lenta3);

void
task3(double q1, double q2, double q3, vector<double> &sol, vector<double> &b1, vector<double> &b2, vector<double> &b3,
      vector<double> &x1, vector<double> &x2, vector<double> &x3, vector<vector<double>> &Lenta1,
      vector<vector<double>> &Lenta2, vector<vector<double>> &Lenta3);

void
task4(double q1, double q2, double q3, vector<double> &sol, vector<double> &b1, vector<double> &b2, vector<double> &b3,
      vector<double> &x1, vector<double> &x2, vector<double> &x3, vector<vector<double>> &Lenta1,
      vector<vector<double>> &Lenta2, vector<vector<double>> &Lenta3);

int main() {
    SetConsoleOutputCP(CP_UTF8);

    srand((unsigned int) time(0));

    vector<vector<double>> A1(N, vector<double>(N, 0));
    vector<vector<double>> A2(N, vector<double>(N, 0));
    vector<vector<double>> A3(N, vector<double>(N, 0));
    vector<vector<double>> AT1(N, vector<double>(N, 0));
    vector<vector<double>> AT2(N, vector<double>(N, 0));
    vector<vector<double>> AT3(N, vector<double>(N, 0));
    vector<vector<double>> M1(N, vector<double>(N, 0));
    vector<vector<double>> M2(N, vector<double>(N, 0));
    vector<vector<double>> M3(N, vector<double>(N, 0));

    double q1 = 1.8;
    double q2 = 2;
    double q3 = 10;
    //рнадомное заполнение
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if ((l + 1) - abs(i - j) > 0)
                A1[i][j] = randomValue(-1, 1);
            A2[i][j] = A1[i][j];
            A3[i][j] = A1[i][j];
        }
    }
    //диагональное преобладание
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A1[i][i] += fabs(A1[i][j]);
            A2[i][i] += fabs(A2[i][j]);
            A3[i][i] += fabs(A3[i][j]);
        }
        A1[i][i] *= q1;
        A2[i][i] *= q2;
        A3[i][i] *= q3;
    }
//    cout << "A" << endl;
//    PrintMatrix(A1);
    vector<double> sol(N, 0);
    for (int i = 0; i < N; i++) {
        sol[i] = randomValue(-1, 1);
    }


    vector<double> rhs1 = MatrixVectorMultiply(N, A1, sol);
    vector<double> rhs2 = MatrixVectorMultiply(N, A2, sol);
    vector<double> rhs3 = MatrixVectorMultiply(N, A3, sol);

    AT1 = MatrixTranspose(N, A1);
    AT2 = MatrixTranspose(N, A2);
    AT3 = MatrixTranspose(N, A3);
//    cout << "A" << endl;
//    PrintMatrix(AT1);
    M1 = MatrixMatrixmult(N, AT1, A1);
    M2 = MatrixMatrixmult(N, AT2, A2);
    M3 = MatrixMatrixmult(N, AT3, A3);
//    cout << "A*" << endl;
//    PrintMatrix(M1);

    vector<double> b1 = MatrixVectorMultiply(N, AT1, rhs1);
    vector<double> b2 = MatrixVectorMultiply(N, AT2, rhs2);
    vector<double> b3 = MatrixVectorMultiply(N, AT3, rhs3);
    vector<double> x1(N, 0);
    vector<double> x2(N, 0);
    vector<double> x3(N, 0);

    // создание ленточных матриц
    vector<vector<double>> Lenta1(N, vector<double>(4 * l + 1, 0));
    vector<vector<double>> Lenta2(N, vector<double>(4 * l + 1, 0));
    vector<vector<double>> Lenta3(N, vector<double>(4 * l + 1, 0));
    Lenta1 = MatrixtoLenta(N, 2 * l, M1, Lenta1);
    Lenta2 = MatrixtoLenta(N, 2 * l, M2, Lenta2);
    Lenta3 = MatrixtoLenta(N, 2 * l, M3, Lenta3);
//    cout << "Lenta" << endl;
//    PrintMatrix(Lenta1);


    task2(q1, q2, q3, sol, b1, b2, b3, x1, x2, x3, Lenta1, Lenta2, Lenta3);

    task3(q1, q2, q3, sol, b1, b2, b3, x1, x2, x3, Lenta1, Lenta2, Lenta3);


    task4(q1, q2, q3, sol, b1, b2, b3, x1, x2, x3, Lenta1, Lenta2, Lenta3);

}

void
task4(double q1, double q2, double q3, vector<double> &sol, vector<double> &b1, vector<double> &b2, vector<double> &b3,
      vector<double> &x1, vector<double> &x2, vector<double> &x3, vector<vector<double>> &Lenta1,
      vector<vector<double>> &Lenta2, vector<vector<double>> &Lenta3) {
    cout << " PCGM " << endl;
    cout << " -------------------------- " << endl;
    cout << " Для q1 = " << q1 << " ";
    x1 = CGMLenta(N, 2 * l, Lenta1, b1);
    norma(N, x1, sol);
    cout << endl;
    cout << " Для q2 = " << q2 << " ";
    x2 = CGMLenta(N, 2 * l, Lenta2, b2);
    norma(N, x2, sol);
    cout << endl;
    cout << " Для q3 = " << q3 << " ";
    x3 = CGMLenta(N, 2 * l, Lenta3, b3);
    norma(N, x3, sol);
    cout << endl;
}

void
task3(double q1, double q2, double q3, vector<double> &sol, vector<double> &b1, vector<double> &b2, vector<double> &b3,
      vector<double> &x1, vector<double> &x2, vector<double> &x3, vector<vector<double>> &Lenta1,
      vector<vector<double>> &Lenta2, vector<vector<double>> &Lenta3) {
      for (double i = 0; i < 2; i += 0.1) {//relax from 0 to 2 with 0.1 step
    	cout << " SOR; relax = " << i << endl;
    	cout << " -------------------------- " << endl;
    	cout << " Для q1 = " << q1 << " "; x1 = SORLenta(N, 2 * l, Lenta1, b1, i);
    	norma(N, x1, sol);
    	cout << endl;
    	cout << " Для q2 = " << q2 << " "; x2 = SORLenta(N, 2 * l, Lenta2, b2, i);
    	norma(N, x2, sol);
    	cout << endl;
    	cout << " Для q3 = " << q3 << " "; x3 = SORLenta(N, 2 * l, Lenta3, b3, i);
    	norma(N, x3, sol);
    	cout << endl;
    }
}

void
task2(double q1, double q2, double q3, vector<double> &sol, vector<double> &b1, vector<double> &b2, vector<double> &b3,
      vector<double> &x1, vector<double> &x2, vector<double> &x3, vector<vector<double>> &Lenta1,
      vector<vector<double>> &Lenta2, vector<vector<double>> &Lenta3) {
    cout << " Якобиан: " << endl;
    cout << " Для q1 = " << q1 << " ";
    x1 = Jacobian(N, 2 * l, Lenta1, b1);
    norma(N, x1, sol);
    cout << endl;
    cout << " Для q2 = " << q2 << " ";
    x2 = Jacobian(N, 2 * l, Lenta2, b2);
    norma(N, x2, sol);
    cout << endl;
    cout << " Для q3 = " << q3 << " ";
    x3 = Jacobian(N, 2 * l, Lenta3, b3);
    norma(N, x3, sol);

    cout << endl;
}
