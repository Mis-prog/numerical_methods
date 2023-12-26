#include <iomanip>

std::vector<double> x;
std::vector<double> prev_x;
std::vector<double> y;
std::vector<double> prev_y;
std::vector<double> _lagrange;
std::vector<double> prev_lagrange;

double Fnc(double x) {
    return x * x * acos(0.9 * x);
}

double Taylor(double x) {

    double value = -0.1500319320e0 + 0.8520793580e0 * x + 0.32249289e-1 * pow(x - 0.5000000000e0, 0.2e1)
                   - 0.1338846316e1 * pow(x - 0.5000000000e0, 0.3e1) - 0.6258143551e0 * pow(x - 0.5000000000e0, 0.4e1)
                   - 0.6616392414e0 * pow(x - 0.5000000000e0, 0.5e1) - 0.7133378805e0 * pow(x - 0.5000000000e0, 0.6e1)
                   - 0.8712005035e0 * pow(x - 0.5000000000e0, 0.7e1) - 0.1105397889e1 * pow(x - 0.5000000000e0, 0.8e1)
                   - 0.1462567861e1 * pow(x - 0.5000000000e0, 0.9e1) - 0.1984806752e1 * pow(x - 0.5000000000e0, 0.10e2)
                   - 0.2752463870e1 * pow(x - 0.5000000000e0, 0.11e2) - 0.3880281350e1 * pow(x - 0.5000000000e0, 0.12e2)
                   - 0.5545644692e1 * pow(x - 0.5000000000e0, 0.13e2) - 0.8015612555e1 * pow(x - 0.5000000000e0, 0.14e2)
                   - 0.1169701898e2 * pow(x - 0.5000000000e0, 0.15e2) - 0.1720929935e2 * pow(x - 0.5000000000e0, 0.16e2)
                   - 0.2549926079e2 * pow(x - 0.5000000000e0, 0.17e2) - 0.3801731712e2 * pow(x - 0.5000000000e0, 0.18e2)
                   - 0.5699122055e2 * pow(x - 0.5000000000e0, 0.19e2) - 0.8585050724e2 * pow(x - 0.5000000000e0, 0.20e2)
                   - 0.1298865230e3 * pow(x - 0.5000000000e0, 0.21e2);

    return value;
}

double calculateCoordinates(int n, double point) {
    double sum = 0;
    for (int i = 0; i <= n; ++i) {
        double mult = 1;
        for (int k = 0; k <= n; ++k) {
            if (i != k) {
                mult *= (point - prev_x[k]) / (prev_x[i] - prev_x[k]);
            }
        }
        sum += prev_y[i] * mult;
    }
    return sum;
}

void task5_main() {
    std::cout << "===== Best Uniform Approximation Polynomial =====" << std::endl;
    double err = 0;
    int N = 100;
    int n = 22;
    double h = (b - a) / N;


    //Векторы для построения ИМЛ для разложения Тейлора (23 точек для 22 степени)
    for (int i = 0; i <= n; ++i) {
        prev_x.push_back((b + a) / 2 + cos((pi * ((double) 2 * i + 1)) / ((double) 2 * (n + 1))) * (b - a) / 2);
        prev_y.push_back(Taylor(prev_x[i]));
    }
    double max_22_err = 0;
    //Построение ИМЛ для разложения Тейлора (22 степень)
    for (int i = 0; i < N; ++i) {
        double x_i = a + i * h;
        double value = calculateCoordinates(n, x_i);
        double difference = abs(Taylor(x_i) - value);
        if (difference >= max_22_err) {
            max_22_err = difference;
        }
        _lagrange.push_back(value);
    }
    std::ofstream buap_n_vs_err("buap_n_vs_err.txt");
    std::cout << "n = 22 error = " << std::fixed << std::setprecision(10) << max_22_err << std::endl;
    buap_n_vs_err << 22 << " " << max_22_err << std::endl;

    //////////////

    for (int i = 0; i <= n - 1; i++) {
        //Векторы для построения ИМЛ для ИМЛ для разложения Тейлора (т.е. 21 степень, 22 точек, строим по ИМЛ 22 степени)
        x.push_back((b + a) / 2 + cos((pi * ((double) 2 * i + 1)) / ((double) 2 * (n + 1))) * (b - a) / 2);
        y.push_back(calculateCoordinates(n, x[i]));
    }

    while (err < epsilon) {
        n--; //21 ..
        //Меняем местами векторы
        prev_x = x;
        x.clear();
        prev_y = y;
        y.clear();
        prev_lagrange = _lagrange;
        _lagrange.clear();
        double max_error = 0;
        for (int i = 0; i < N; ++i) {
            double x_i = a + i * h;
            //Построение ИМЛ 21... степени
            _lagrange.push_back(calculateCoordinates(n, x_i));
            if (i <= n - 1) { //0..20 -> 21 точек, строим по ИМЛ 21 степени
                x.push_back((b + a) / 2 + cos((pi * ((double) 2 * i + 1)) / ((double) 2 * (n + 1))) * (b - a) / 2);
                y.push_back(calculateCoordinates(n, x[i]));
            }
            double difference = abs(prev_lagrange[i] - _lagrange[i]);
            if (difference >= max_error) {
                max_error = difference;
            }
        }
        err = max_error;
        std::cout << "n = " << n << " error = " << std::fixed << std::setprecision(10) << err << std::endl;
        buap_n_vs_err << n << " " << err << std::endl;
    }

    ofstream file("node_task5.txt");

    for (int i = 0; i < n; i++) {
        file << x[i] << " " << Taylor(x[i]) << endl;
    }
    file.close();
    n++;
    std::cout << "Optimal n: " << n << std::endl;
    buap_n_vs_err.close();
    system("python D:/5sem/numerical/practice/labs/Lab1/src/plot/plot_5.py");
}
