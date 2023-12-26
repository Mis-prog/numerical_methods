#include "task.h"

std::vector<double> SquareRootMethod(const std::vector<std::vector<double>>& matrix) {
    int dim = matrix.size();
    std::vector<std::vector<double>> U(dim);
    for (int i = 0; i < dim; ++i) {
        U[i].resize(dim);
        U[i][i] = matrix[i][i];
        for (int k = 0; k <= i - 1; ++k) {
            U[i][i] -= U[k][i] * U[k][i];
        }
        U[i][i] = sqrt(U[i][i]);
        for (int j = 1; j < dim; ++j) {
            if (j > i) {
                U[i][j] = matrix[i][j];
                for (int k = 0; k <= i - 1; ++k) {
                    U[i][j] -= U[k][i] * U[k][j];
                }
                U[i][j] /= U[i][i];
            }
        }
    }
    std::cout << "U:" << std::endl;
    print_matrix(U,1);
    std::vector<double> y(dim);
    for (int i = 0; i < dim; ++i) {
        y[i] = matrix[i][dim];
        for (int k = 0; k <= i - 1; ++k) {
            y[i] -= U[k][i] * y[k];
        }
        y[i] /= U[i][i];
    }
    std::vector<double> x(dim);
    for (int i = dim - 1; i >= 0; --i) {
        x[i] = y[i];
        for (int k = i + 1; k < dim; ++k) {
            x[i] -= U[i][k] * x[k];
        }
        x[i] /= U[i][i];
    }
    return x;
}

double f(double x) {
    return x*x*acos(0.9*x);
}

void Task3() {
    double a = 0;
    double b = 1;
    int n = 20;
    std::vector<double> x_i;
    std::vector<double> y_i;
    double h = (b - a) / n;
    ofstream node("node_task3.txt");
    for (int i = 0; i < n; ++i) {
        double x = a + i * h;
        x_i.push_back(x);
        y_i.push_back(f(x));
        node << x << " " << f(x) << endl;
    }
    node.close();
    std::vector<double> answer;
    std::vector<std::vector<double>> answers;
    std::vector<std::vector<double>> matrix;
    //Polynoms with max degree 1...12
    for (int m = 2; m < 14; ++m) {
        matrix.clear();
        matrix.resize(m);
        for (int i = 0; i < m; ++i) {
            matrix[i].resize(m + 1);
            for (int j = 0; j < m; ++j) {
                for (int k = 0; k < n; ++k) {
                    matrix[i][j] += pow(x_i[k], i + j);
                }
            }
            for (int k = 0; k < n; ++k) {
                matrix[i][m] += y_i[k] * pow(x_i[k], i);
            }
        }
        std::cout << "Система:" << std::endl;
        print_matrix(matrix,1);
        answer = SquareRootMethod(matrix);
        std::cout << "Решение системы: " << std::endl;
        print_vector(answer,1);
        answers.push_back(answer);
    }
    //Graphics
    int N = 100;
    h = (b - a) / N;
    std::ofstream task3("task3.txt");
    for (int i = 0; i <= N; ++i) {
        double x = a + i * h;
        double f = 0;
        int count = 0;
        task3 << x << " ";
        for (int k = 0; k < 12; ++k) {
            f = 0;
            for (int j = 0; j < k + 2; ++j) {
                f += answers[k][j] * pow(x, j);
            }
            task3 << f << " ";
        }
        task3 << std::endl;
    }
    task3.close();

    std::cout << "Полиномы" << std::endl;
    std::vector<double> sum_of_squares_of_deviations(12);
    for (int i = 0; i < x_i.size(); ++i) {
        for (int k = 0; k < 12; ++k) {
            double f = 0;
            for (int j = 0; j < k + 2; ++j) {
                f += answers[k][j] * pow(x_i[i], j);
            }
            sum_of_squares_of_deviations[k] += pow(abs(f - y_i[i]), 2);
        }
    }
    double min_value = sum_of_squares_of_deviations[0];
    double min_n = 0;
    std::cout << "n = " << 1 << ": " << sum_of_squares_of_deviations[0] << std::endl;
    for (int i = 1; i < 12; ++i) {
        if (sum_of_squares_of_deviations[i] < min_value) {
            min_value = sum_of_squares_of_deviations[i];
            min_n = i;
        }
        std::cout << "n = " << (i + 1) << " сумма квадратов отклонений: " << std::setprecision(9) << sum_of_squares_of_deviations[i] << std::endl;
    }
    std::cout << "Лучшие количество узлов: " << std::endl;
    std::cout << "  n = " << (min_n + 1) << " сумма квадратов отклонений: " << min_value << std::endl;
    system("python D:\\5sem\\numerical\\practice\\labs\\Lab3\\src\\plot\\task3.py");
}
