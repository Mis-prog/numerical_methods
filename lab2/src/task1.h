#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <windows.h>
#include <fstream>
#include <random>
#include <iomanip>

using namespace std;

const double PI = 3.141592653589793;
double acos_foo(double x) {
    return x * x * acos(0.9 * x);
}

const int a = 0, b = 1;
const double epsilon = 2 * 1e-4;
const double answer = 0.268487278503810;

double nodeEqualsFill(vector<double> &x, vector<double> &y, int n0) {
    double h = (b - a) / (double) n0, x_cur = 0;
    for (int i = 0; i <= n0; i++) {
        x[i] = x_cur;
        y[i] = acos_foo(x_cur);
        x_cur += h;
    }
    return h;
}

double rectangle(int n0) {
    vector<double> x(n0 + 1), y(n0 + 1);
    double sum_rect = 0, h = nodeEqualsFill(x, y, n0);
    for (int i = 1; i <= n0; i++) {
        sum_rect += h * acos_foo((x[i - 1] + x[i]) / 2.0);
    }
    return sum_rect;
}

double trapezoid(int n0) {
    vector<double> x(n0 + 1), y(n0 + 1);
    double sum_trap = 0, h = nodeEqualsFill(x, y, n0);
    sum_trap = h * (acos_foo(a) + acos_foo(b)) / 2.0;
    for (int i = 1; i <= n0 - 1; i++) {
        sum_trap += h * acos_foo(x[i]);
    }
    return sum_trap;
}


void task1_main() {
    int best_rect, best_trap;
    double rect_cur, trap_cur;
    bool check_rect = 0, check_trap = 0;
    ofstream out1;
    out1.open("task1.txt");
    for (int i = 0; i < 1e4; i++) {
        rect_cur = abs(answer-rectangle(i));
        trap_cur = abs(answer-trapezoid(i));
        out1 << i << "," << rect_cur << "," << trap_cur << endl;
        if (rect_cur < epsilon and !check_rect) {
            best_rect = i;
            check_rect = 1;
        }
        if (trap_cur < epsilon and !check_trap) {
            best_trap = i;
            check_trap = 1;
        }
    }
    out1.close();
    cout << "Прямоугольники" << endl;
    cout << "Оптимальное n: " << best_rect << endl;
    cout << "Значение: " << fixed << setprecision(10) << rectangle(best_rect) << endl;
    cout << "Трапеции" << endl;
    cout << "Оптимальное n: " << best_trap << endl;
    cout << "Значение: " << fixed << setprecision(10) << trapezoid(best_trap) << endl;
    system("python D:/5sem/numerical/Lab2/src/plot/plot_1.py");
}

