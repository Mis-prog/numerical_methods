
#include <iomanip>

double process_Aitkin(bool check) {
    if (check) {
        double q = 0.7;
        int n = 1000;
        double h1 = (b - a) / (double) n;
        double h2 = h1 * q, h3 = h1 * q * q;
        double F1 = rectangle(n), F2 = rectangle(int((b - a) / h2)), F3 = rectangle(int((b - a) / h3));
        double B = (F1 - F2) / (F2 - F3);
        double p = -log(B) / log(q);
        return p;
    } else {
        double q = 0.7;
        int n = 1000;
        double h1 = (b - a) / (double) n;
        double h2 = h1 * q, h3 = h1 * q * q;
        double F1 = trapezoid(n), F2 = trapezoid(int((b - a) / h2)), F3 = trapezoid(int((b - a) / h3));
        double B = (F1 - F2) / (F2 - F3);
        double p = -log(B) / log(q);
        return p;
    }
}

void Rung() {
    int n = 1000;
    cout << "Прямоугольник:\n";
    double p = process_Aitkin(1);
    cout << "    p = " << " " << fixed << setprecision(10) << p << "\n";
    double I_2n = rectangle(2 * n), I_n = rectangle(n);
    double I = I_2n + (pow(2, p) * (I_n - I_2n)) / (double) (pow(2, p) - 1);
    cout.precision(7);
    cout << "  Rung: " << fixed << setprecision(10) << I << "\n    Vakue: " << answer << "\n";

    cout << "Трапеции:\n";
    p = process_Aitkin(0);
    cout << "    p = " << " " << fixed << setprecision(10) << p << "\n";
    I_2n = trapezoid(2 * n);
    I_n = trapezoid(n);
    I = I_2n + (pow(2, p) * (I_n - I_2n)) / (double) (pow(2, p) - 1);
    cout.precision(7);
    cout << "  Rung: " << fixed << setprecision(10) << I << "\n    Vakue: " << answer << "\n";
}

//double h(int n, double a, double b) {
//    return (b - a) / pow(2.0, n);
//}
//
//double R(int n, int m, double a, double b) {
//    if (m == 0) {
//        if (n == 0) {
//            return h(1, a, b) * (acos_foo(a) + acos_foo(b));
//        } else {
//            double sum = 0.5 * R(n - 1, 0, a, b);
//            for (int k = 1; k <= pow(2, n - 1); k++) {
//                sum += h(n, a, b) * acos_foo(a + (2 * k - 1) * h(n, a, b));
//            }
//            return sum;
//        }
//    } else {
//        return (pow(4.0, m) * R(n, m - 1, a, b) - R(n - 1, m - 1, a, b)) / (pow(4.0, m) - 1);
//    }
//}

double Det(std::vector<std::vector<double>> matrix) {
    for (int i = 0; i <= matrix.size() - 1; ++i) {
        for (int j = i + 1; j <= matrix.size() - 1; ++j) {
            double coeff = -matrix[j][i] / matrix[i][i];
            for (int k = 0; k < matrix.size(); ++k) {
                matrix[j][k] += coeff * matrix[i][k];
            }
        }
    }
    double det = 1;
    for (int i = 0; i <= matrix.size() - 1; ++i) {
        det *= matrix[i][i];
    }
    return det;
}

void Ronberg() {
    cout << "Прямоугольник:\n";
    double p = process_Aitkin(1);
    std::cout << "  Romberg: " << std::endl;
    double err = 1;
    double count = 2;
    std::vector<std::vector<double>> up, down;
    do {
        up.resize(count);
        down.resize(count);
        for (int i = 0; i < count; ++i) {
            up[i].resize(count);
            down[i].resize(count);
            up[i][0] = rectangle(pow(2, i));
            down[i][0] = 1;
        }
        for (int i = 0; i < count; ++i) {
            for (int j = 1; j < count; ++j) {
                double h = (b - a) / (pow(2, i));
                up[i][j] = pow(h, p + j - 1);
                down[i][j] = pow(h, p + j - 1);
            }
        }
        double det = Det(up) / Det(down);
        err = abs(answer - det);
        std::cout << "    Number of grids = " << count << " Error: " << err << std::endl;
        ++count;
    } while (err > 1e-6);


    cout << "Трапеции:\n";
    p = process_Aitkin(0);
    std::cout << "  Romberg: " << std::endl;
    err = 1;
    count = 2;
    up.clear();
    down.clear();
    do {
        up.resize(count);
        down.resize(count);
        for (int i = 0; i < count; ++i) {
            up[i].resize(count);
            down[i].resize(count);
            up[i][0] = trapezoid(pow(2, i));
            down[i][0] = 1;
        }
        for (int i = 0; i < count; ++i) {
            for (int j = 1; j < count; ++j) {
                double h = (b - a) / (pow(2, i));
                up[i][j] = pow(h, p + j - 1);
                down[i][j] = pow(h, p + j - 1);
            }
        }
        double det = Det(up) / Det(down);
        err = abs(answer - det);
        std::cout << "    Number of grids = " << count << " Error: " << err << std::endl;
        ++count;
    } while (err > 1e-6);
}


void task3_main() {
    Rung();
    Ronberg();
}