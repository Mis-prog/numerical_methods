

double devideDiff(int i, int j, vector<double> &X, vector<double> &Y) {
    if (j - i == 1) return (Y[j] - Y[i]) / (X[j] - X[i]);
    else return (devideDiff(i + 1, j, X, Y) - devideDiff(i, j - 1, X, Y)) / (X[j] - X[i]);
}

double NewTonEval(vector<double> &XN, vector<double> &YN) {
    double summ_of_Newton = 0;
    double product_of_Newton = 1;
    double sup = -1000;
    vector<double> DevidedDiffs;
    ofstream out3;
    out3.open("task3.txt");
    for (int i = 1; i < XN.size(); i++) {
        DevidedDiffs.push_back(devideDiff(0, i, XN, YN));
    }
    double a = 0, b = 1, diff = 0;
    double h_curr = (b - a) / (double) 1e5, x_cur = 0;
    while (x_cur <= 1) {
        summ_of_Newton = 0;
        for (int j = 1; j < XN.size(); j++) {
            product_of_Newton = 1;
            for (int k = 0; k < j; k++) {
                product_of_Newton *= (x_cur - XN[k]);
            }
            summ_of_Newton += DevidedDiffs[j - 1] * product_of_Newton;
        }
        diff = abs(acos_foo(x_cur) - summ_of_Newton);
        out3 << x_cur << " " << diff << endl;
        if (diff > sup) {
            sup = diff;
        }
        x_cur += h_curr;
    }
    out3.close();
    return sup;
}

void task3_main(int n0) {
    vector<double> x(n0 + 1, 0), y(n0 + 1, 0);
    nodeFillEquals(x, y, n0);
    ofstream out3_test;
    out3_test.open("test3.txt");
    for (int i=0;i<=n0;i++){
        out3_test << x[i] << " " << y[i] << endl;
    }
    cout << "Интерполяция Ньютоном(равномерная сетка): " << NewTonEval(x, y) << endl;
    system("python D:/5sem/numerical/practice/labs/Lab1/src/plot/plot_3.py");

}