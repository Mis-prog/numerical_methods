
const double PI = acos(-1.0);

void nodeFillNotEquals(vector<double> &x, vector<double> &y, int n0) {
    int a = 0, b = 1;
    for (int i = 0; i <= n0; i++) {
        x[i] = (b + a) / 2.0 + ((b - a) / 2.0) * cos((PI * (2.0 * i + 1)) / (2.0 * n0));
        y[i] = acos_foo(x[i]);
    }
}

double task2(vector<double> &x, vector<double> &y, int n0) {
    ofstream out2_1,out2_1_2;
    out2_1.open("task2.txt");
    out2_1_2.open("task2_plot.txt");
    double a = 0, b = 1;
    double h_accurace = (b - a) / (double) 1e5;
    double x_current = 0;
    double diff, sup = -1000;
    double y_cur=0;
    while (x_current <= b) {
        y_cur=lagrange(x, y, x_current, n0);
        diff = abs(acos_foo(x_current) -y_cur);
        out2_1 << x_current << " " << diff << endl;
        out2_1_2 << x_current << " " << y_cur << endl;
        if (diff > sup) {
            sup = diff;
        }
        x_current += h_accurace;
    }
    out2_1.close();
    out2_1_2.close();
    return sup;
}


void task2_main(int n0) {
    vector<double> x(n0 + 1, 0), y(n0 + 1, 0);
    nodeFillNotEquals(x, y, n0);
    ofstream out_point;
    out_point.open("notequalsnode.txt");
    for (int i=0;i<x.size();i++){
        out_point << x[i] << " " << y[i] << endl;
    }
    out_point.close();
    cout  << "Неравномерная сетка: " << task2(x, y, n0) << endl;
    system("python D:/5sem/numerical/practice/labs/Lab1/src/plot/plot_2.py");
}