#include "task.h"

namespace task2 {
    const double a = -7, b = -5, c = 2, d = 6, epsilon = 1e-7;
}

double task2::f(double x, double y) {
    return 1 - sin(x + log(y)) + x * x + 12 * x;
}

double task2::diff_x(double x, double y) {
    return -cos(x + log(y)) + 2 * x + 12;
}

double task2::diff_y(double x, const double y) {
    return -cos(x + log(y)) / y;
}

double task2::phi_x(double x, double y) {
    return x - 1. / (sin(-6 + log(y)) + 2) * diff_x(x, y);
}

double task2::phi_y(double x, double y) {
    return y - 16. / (cos(x + log(4)) + sin(x + log(4))) * diff_y(x, y);
}

pair<double, double> task2::SimpleIterations(double x_1, double x_2, double y_1, double y_2) {
    if (x_1 > x_2) {
        std::swap(x_1, x_2);
    }
    if (y_1 > y_2) {
        std::swap(y_1, y_2);
    }
    double x = (x_1 + x_2) / 2;
    double y = (y_1 + y_2) / 2;
    double x_next = phi_x(x, y);
    double y_next = phi_y(x, y);
    while (std::max(abs(x_next - x), abs(y_next - y)) > epsilon) {
        x = x_next;
        y = y_next;
        x_next = phi_x(x, y);
        y_next = phi_y(x, y);
    }
    return {x_next, y_next};
}

void task2::main_task2(){
    std::pair<double, double> min = SimpleIterations(a, b, c, d);
    std::cout << "x = " << min.first << ", y = " << min.second << ", f(x,y) = " << f(min.first, min.second)
              << std::endl;
}


