
double Monte_Carlo(int n) {
    double xk = RAND_MAX / (double) (b - a);
    srand(time(NULL));
    double S = 0.0;
    for (int k = 0; k < 100; k++) {
        double sum = 0.0;
        for (int i = 0; i < n; i++) {
            double x = rand() / xk + a;
            sum += acos_foo(x);
        }
        sum = sum * (b - a) / n;
        S += sum;
    }
    S /= 100;
    return S;
}

void task6_main() {
    ofstream out6;
    double best_node=-11;
    out6.open("task6.txt");
    for (int i = 1; i < 2e3; i++) {
        out6 << i << " " << abs(epsilon - Monte_Carlo(i)) << endl;
        if (abs(epsilon - Monte_Carlo(i)) > best_node) {
            best_node = abs(epsilon - Monte_Carlo(i));
        }
    }
    out6.close();
    system("python D:\\5sem\\numerical\\practice\\labs\\Lab2\\src\\plot\\plot_6.py");
}