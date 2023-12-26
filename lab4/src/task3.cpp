#include "task.h"

namespace task3 {
    const double a = -7, b = -5, c = 2, d = 6, epsilon = 1e-7;
}

double task3::df_x_x(double x, double y) {
    return sin(x + log(y)) + 2;
}

double task3::df_x_y(double x, double y) {
    return sin(x + log(y)) / y;
}

double task3::df_y_x(double x, double y) {
    return sin(x + log(y)) / y;
}

double task3::df_y_y(double x, double y) {
    return (cos(x + log(y)) + sin(x + log(y))) / (y * y);
}

pair<double, double> task3::Newton(double x_1, double x_2, double y_1, double y_2) {
    if (x_1 > x_2) {
        std::swap(x_1, x_2);
    }
    if (y_1 > y_2) {
        std::swap(y_1, y_2);
    }
    double x = (x_1 + x_2) / 2;
    double y = (y_1 + y_2) / 2;
    std::vector<double> answer;
    std::vector<std::vector<double>> matrix(2);
    matrix[0].resize(3);
    matrix[1].resize(3);
    matrix[0][0] = df_x_x(x, y);
    matrix[0][1] = df_x_y(x, y);
    matrix[1][0] = df_y_x(x, y);
    matrix[1][1] = df_y_y(x, y);
    matrix[0][2] = -task2::diff_x(x, y);
    matrix[1][2] = -task2::diff_y(x, y);
    answer = Gauss(matrix);
    double x_next = x + answer[0];
    double y_next = y + answer[1];
    while (std::max(abs(answer[0]), abs(answer[1])) > epsilon) {
        x = x_next;
        y = y_next;
        matrix[0][0] = df_x_x(x, y);
        matrix[0][1] = df_x_y(x, y);
        matrix[1][0] = df_y_x(x, y);
        matrix[1][1] = df_y_y(x, y);
        matrix[0][2] = -task2::diff_x(x, y);
        matrix[1][2] = -task2::diff_y(x, y);
        answer = Gauss(matrix);
        x_next = x + answer[0];
        y_next = y + answer[1];
    }
    return {x_next, y_next};
}

void task3::main_task3() {
    std::pair<double, double> min = Newton(a, b, c, d);
    std::cout << "x = " << min.first << ", y = " << min.second << ", f(x,y) =  " << task2::f(min.first, min.second)
              << std::endl;
}

std::vector<double> task3::Gauss(std::vector<std::vector<double>> matrix) {
    int dim = matrix.size();
    for (int i = 0; i < dim; ++i) {
        for (int k = 0; k < dim - 1; ++k) {
            double max = 0;
            double m_index = 0;
            for (int m = k; m < dim; ++m) {
                if (abs(matrix[m][k]) > max) {
                    max = abs(matrix[m][k]);
                    m_index = m;
                }
            }
            if (max == 0) {
                std::cout << "There is no single solution" << std::endl;
                return {-1};
            }
            for (int i = 0; i <= dim; ++i) {
                double temp = matrix[k][i];
                matrix[k][i] = matrix[m_index][i];
                matrix[m_index][i] = temp;
            }
        }
        //std::cout << "The result of the shuffle of rows: " << std::endl;
        //PrintMatrix(matrix);
        //����������
        for (int j = i + 1; j < dim; ++j) {
            double coeff = -matrix[j][i] / matrix[i][i];
            for (int k = 0; k <= dim; ++k) {
                matrix[j][k] += coeff * matrix[i][k];
            }
        }
        //PrintMatrix(matrix);
    }
    //std::cout << "The result of a direct process:  " << std::endl;
    std::vector<double> answer(dim);
    answer[dim - 1] = matrix[dim - 1][dim] / matrix[dim - 1][dim - 1];
    for (int i = dim - 2; i >= 0; --i) {
        answer[i] = matrix[i][dim];
        for (int j = i + 1; j < dim; ++j) {
            answer[i] -= matrix[i][j] * answer[j];
        }
        answer[i] /= matrix[i][i];
    }
    return answer;
}