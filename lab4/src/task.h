#include <iostream>
#include <vector>
#include <windows.h>
#include <math.h>
#include <iomanip>

using namespace std;


namespace task1 {
    const double a = -5, b = 5, epsilon = 1e-5;

    double foo_task1(double x);

    double foo_task1_diff(double x);

    double x1_foo_task1(double x);

    double x2_foo_task2(double x);

    double x1_foo_task1_diff(double x);

    double x2_foo_task2_diff(double x);


    void BIM(double a, double b, int &num_it);

    void NEM(double a, double b, int &num_it);

    void SEM(double a, double b, int &num_it);

    void CHM(double a, double b, int &num_it);

    pair<double,int> SIM(double a, double b, std::function<double(const double&)> f);

    void main_task1();

}

namespace task2 {
    double f(double x, double y);

    double diff_x(double x, double y);

    double diff_y(double x, const double y);

    double phi_x(double x, double y);

    double phi_y(double x, double y);

    pair<double, double> SimpleIterations(double x_1, double x_2, double y_1, double y_2);

    void main_task2();
}

namespace task3 {
    vector<double> Gauss(std::vector<std::vector<double>> matrix);

    double df_x_x(double x, double y);

    double df_x_y(double x, double y);

    double df_y_x(double x, double y);

    double df_y_y(double x, double y);

    pair<double, double> Newton(double x_1, double x_2, double y_1, double y_2);

    void main_task3();
}