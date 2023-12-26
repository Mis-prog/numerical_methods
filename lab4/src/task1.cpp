#include "task.h"

double task1::foo_task1(double x) {
    return 20 * log(2 + cos(x)) - x - 10;
}

double task1::foo_task1_diff(double x) {
    return (-20 * sin(x)) / (2 + cos(x)) - 1;
}

double task1::x1_foo_task1(double x) {
    return 20 * log(2 + cos(x)) - 10;
}

double task1::x2_foo_task2(double x) {
    return acos(exp((x / 20.0 + 0.5)) - 2);
}

double task1::x1_foo_task1_diff(double x) {
    return (-20 * sin(x)) / (2 + cos(x));
}

double task1::x2_foo_task2_diff(double x) {
    return (-exp(x / 20.0 + 0.5) / (20 * sqrt(-(exp(x / 20.0 + 0.5) - 2) * (exp(x / 20.0 + 0.5) - 2) + 1)));
}


void task1::main_task1() {
    vector<double> answer = {-4.00424191074621, -2.11371014988160, 1.77077248495832, 4.80946952510987};
    int n_bim = 0, n_nem = 0, n_sem = 0, n_chm = 0, n_sim = 0;
    int N = 11;
    double h = (b - a) / N;
    double x_cur = a;
    while (x_cur < b) {
        double x0 = x_cur;
        double x1 = x_cur + h;
        cout << setprecision(2) << "Корни в этом отрезке: [" << x0 << ", " << x1 << "]" << endl;
        BIM(x0, x1, n_bim);
        NEM(x0, x1, n_nem);
        SEM(x0, x1, n_sem);
        CHM(x0, x1, n_chm);
        x_cur += h;
    }
    cout << "Корни:\n";
    for (auto i: answer) {
        cout << i << " ";
    }
    cout << endl;
}

void task1::BIM(double a, double b, int &num_it) {
    double c = (a + b) / 2.0;
    if ((b - a) < 2 * epsilon) {
        cout << "Метод биекции:" << endl;
        cout << "Корень: " << fixed << setprecision(9) << c << endl;
        cout << "Количество итераций: " << num_it << endl;
        cout << "----------------\n";
        return;
    } else {
        num_it++;
        if (foo_task1(a) * foo_task1(c) <= 0) {
            BIM(a, c, num_it);
        } else if (foo_task1(c) * foo_task1(b) < 0) {
            BIM(c, b, num_it);
        }
    }
}


// Метод касательных(Ньютона)
void task1::NEM(double a, double b, int &num_it) {
    double x0 = a;
    double x1 = x0 - foo_task1(x0) / foo_task1_diff(x0);
    // что-то похожее на градиентный спуск, х1 будет постоянно двигаться, пока не сойдется
    while (abs(x1 - x0) > epsilon) {
        x0 = x1;
        x1 = x0 - foo_task1(x0) / foo_task1_diff(x0);
        num_it++;
    }
    if (a <= x1 && x1 <= b) {
        cout << "Метод Ньютона(касательных):" << endl;
        cout << "Корень: " << fixed << setprecision(9) << x1 << endl;
        cout << "Количество итераций: " << num_it << endl;
        cout << "----------------\n";
    }
}

// Метод секущих
void task1::SEM(double a, double b, int &num_it) {
    int count_itr = 0;
    double x0 = a;
    double x1 = b;
    double x2 = x1 - foo_task1(x1) * (x1 - x0) / (foo_task1(x1) - foo_task1(x0));
    // отличается лишь точным вычислением производной от ньютона
    while (abs(x2 - x1) > epsilon) {
        x0 = x1;
        x1 = x2;
        x2 = x1 - foo_task1(x1) * (x1 - x0) / (foo_task1(x1) - foo_task1(x0));
        count_itr++;
    }
    if (a <= x2 && x2 <= b) {
        cout << "Метод секущих:" << endl;
        cout << "Корень: " << fixed << setprecision(9) << x2 << endl;
        cout << "Количество итераций: " << count_itr << endl;
        cout << "----------------\n";
    }
}

// Метод хорд
void task1::CHM(double a, double b, int &num_it) {
    double x0 = a;
    double x1 = x0 - foo_task1(x0) * (x0 - b) / (foo_task1(x0) - foo_task1(b));
    // здесь мы как бы строим хорды от фиксированного конца б
    while (abs(x1 - x0) > epsilon) {
        x0 = x1;
        x1 = x0 - foo_task1(x0) * (x0 - b) / (foo_task1(x0) - foo_task1(b));
        num_it++;
    }
    if (a <= x1 && x1 <= b) {
        cout << "Метод хорд:" << endl;
        cout << "Корень: " << fixed << setprecision(9) << x1 << endl;
        cout << "Количество итераций: " << num_it << endl;
        cout << "----------------\n";
    }
}


//// Метод простых итераций
//void task1::SIM(double a, int &n_num) {
//    double x0 = a;
//    double x1 = x2_foo_task2(x0);
//    while (abs(x1 - x0) > epsilon) {
//        x0 = x1;
//        x1 = x2_foo_task2(x0);
//        n_num++;
//    }
//    cout << "Метод простых итераций:" << endl;
//    cout << "Корень: " << x1 << fixed << setprecision(9) << endl;
//    cout << "Количество итераций: " << n_num << endl;
//    cout << "----------------\n";
//    } else if ((dF2(a) < 1) && (dF2(b) < 1)) {
//        int num_it = 0;
//        double x0 = b;
//        double x1 = F2(x0);
//        //  смотрим пока разница вида f(f....(n-1)...f(b)...) f(f....(n)...f(b)...) не сойдется
//        while (abs(x1 - x0) > delta) {
//            x0 = x1;
//            x1 = F2(x0);
//            num_it++;
//        }
//        cout << "Метод простых итераций:" << endl;
//        cout << "f(x) = 6/x-2/x^2-1/x^3" << endl;
//        cout << "Корень: " << fixed << setprecision(9) << x1 << endl;
//        cout << "Количество итераций: " << num_it << endl;
//        cout << "----------------\n";
//    } else if ((dF3(a) < 1) && (dF3(b) < 1)) {
//        int num_it = 0;
//        double x0 = b;
//        double x1 = F3(x0);
//        //  смотрим пока разница вида f(f....(n-1)...f(b)...) f(f....(n)...f(b)...) не сойдется
//        while (abs(x1 - x0) > delta) {
//            x0 = x1;
//            x1 = F3(x0);
//            num_it++;
//        }
//        cout << "Метод простых итераций:" << endl;
//        cout << "f(x) = x^3/6+1/3+1/6x" << endl;
//        cout << "Корень: " << fixed << setprecision(9) << x1 << endl;
//        cout << "Количество итераций: " << num_it << endl;
//        cout << "----------------\n";
//    }
//}


