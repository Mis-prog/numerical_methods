double f_xt(double x, double a = 0, double b = 1) {
    double t = (b + a) / 2.0 + x * (b - a) / 2.0;
    return acos_foo(t);
}

double Lejandr(int count) {

    switch (count) {
        case 0:
            return 2.0 * f_xt(0);
        case 1:
            return f_xt(-0.5773502692) + f_xt(0.5773502692);
        case 2:
            return 0.5555555556 * f_xt(-0.7745966692) +
                   0.5555555556 * f_xt(0.7745966692) +
                   0.8888888888 * f_xt(0);
        case 3:
            return 0.3478547451 * f_xt(-0.8611363115) +
                   0.6521451549 * f_xt(-0.3399810436) +
                   0.6521451549 * f_xt(0.3399810436) +
                   0.3478547451 * f_xt(0.8611363115);
        case 4:
            return 0.2369268851 * f_xt(-0.9061798459) +
                   0.4786286705 * f_xt(-0.5384693101) +
                   0.5688888888 * f_xt(0) +
                   0.2369268851 * f_xt(0.9061798459) +
                   0.4786286705 * f_xt(0.5384693101);
        case 5:
            return 0.1713244924 * f_xt(-0.9324695142) +
                   0.3607615730 * f_xt(-0.6612093684) +
                   0.4679139346 * f_xt(-0.2386191861) +
                   0.1713244924 * f_xt(0.9324695142) +
                   0.3607615730 * f_xt(0.6612093684) +
                   0.4679139346 * f_xt(0.2386191861);
        case 6:
            return 0.12948496 * (f_xt(0.94910791) + f_xt(-0.94910791)) +
                   0.27970540 * (f_xt(0.74153119) + f_xt(-0.74153119)) +
                   0.38183006 * (f_xt(0.40584515) + f_xt(-0.40584515)) +
                   0.41795918 * f_xt(0);
        case 7:
            return 0.10122854 * (f_xt(0.96028986) + f_xt(-0.96028986)) +
                   0.22238104 * (f_xt(0.79666648) + f_xt(-0.79666648)) +
                   0.31370664 * (f_xt(0.52553242) + f_xt(-0.52553242)) +
                   0.36268378 * (f_xt(0.18343464) + f_xt(-0.18343464));
        default:
            return 0;
    }

}

void task4_main() {
    int bestCount = 0;
    ofstream task4("task4.txt");
    bool check = 1;
    for (int i = 0; i <= 7; ++i) {
        task4 << i << " " << fixed << setprecision(10) << abs(answer-Lejandr(i) / 2.0) << endl;
        std::cout << "i: " << i << " " << fixed << setprecision(10) << Lejandr(i) / 2.0 << std::endl;
        if (abs((Lejandr(i) / 2.0) - answer) < epsilon && check) {
            bestCount = i;
            check = 0;
        }
    }
    cout << "Оптимальное число: " << bestCount << endl;
    task4.close();
    system("python D:\\5sem\\numerical\\practice\\labs\\Lab2\\src\\plot\\plot_4.py");
}