struct SplineTuple {
    double a, b, c, d, t_i;
};


double buildSpline(vector<double> &x, vector<double> &y) {
    int n = x.size() - 1;

    vector<double> h;
    h.push_back(0);
    for (int i = 1; i <= n; i++) {
        h.push_back(x[i] - x[i - 1]);
    }

    vector<SplineTuple> spline_value(n + 1, {0, 0, 0, 0, 0});
    vector<double> alfa(n + 1, {0}), betta(n + 1, {0});
    vector<double> A(n + 1, {0}), B(n + 1, {1}), C(n + 1, {0}), F(n + 1, {0});

    for (int i = 2; i <= n; i++) {

        A[i - 1] = h[i - 1];
        B[i - 1] = -2 * (h[i] + h[i - 1]);
        C[i - 1] = h[i];
        F[i - 1] = 3 * ((y[i] - y[i - 1]) / h[i] - (y[i - 1] - y[i - 2]) / h[i - 1]);
    }

    for (int i = 1; i <= n; i++) {
        alfa[i] = (-C[i - 1] / (A[i - 1] * alfa[i - 1] - B[i - 1]));
        betta[i] = (F[i - 1] - A[i - 1] * betta[i - 1]) / (A[i - 1] * alfa[i - 1] - B[i - 1]);
    }


    for (int i = n - 1; i > 0; i--) {
        spline_value[i].c = alfa[i + 1] * spline_value[i + 1].c + betta[i + 1];
    }


    for (int i = 1; i < n; i++) {
        spline_value[i].t_i = x[i];

        spline_value[i].a = y[i - 1];
        spline_value[i].b = (y[i] - y[i - 1]) / h[i] - h[i] * (spline_value[i + 1].c + 2 * spline_value[i].c) / 3;
        spline_value[i].d = (spline_value[i + 1].c - spline_value[i].c) / (3 * h[i]);
    }
    spline_value[n].a = y[n - 1];
    spline_value[n].b = ((y[n] - y[n - 1]) / h[n] - 2 * h[n] * spline_value[n].c / 3);
    spline_value[n].d = (-spline_value[n].c / (3 * h[n]));
    spline_value[n].t_i = x[n];
//    int i_cur=0;
//    for (SplineTuple i: spline_value) {
//        cout << i_cur <<" " << i.a << " " << i.b << " " << i.c << " " << i.d << " " << i.t_i << endl;
//        i_cur++;
//    }
    ofstream out6;
    out6.open("task6.txt");
    int a = 0, b = 1;
    double pogr_otr = (b - a) / (double) 1e5;
    int flag = 1;
    double x_cur = 0, y_pogr = -1000, yDelta, delta;
    while (x_cur < 1) {
        if (x_cur <= spline_value[flag].t_i) {
            double delta_x = x_cur - spline_value[flag].t_i;
            yDelta = spline_value[flag].a + delta_x * spline_value[flag].b + delta_x * delta_x * spline_value[flag].c +
                     delta_x * delta_x * delta_x * spline_value[flag].d;
            delta = abs(acos_foo(x_cur) - yDelta);
            out6 << x_cur << " " << delta << endl;
        } else {
            flag++;
            double delta_x = x_cur - spline_value[flag].t_i;
            yDelta = spline_value[flag].a + delta_x * spline_value[flag].b + delta_x * delta_x * spline_value[flag].c +
                     delta_x * delta_x * delta_x * spline_value[flag].d;
            delta = abs(acos_foo(x_cur) - yDelta);
            out6 << x_cur << " " << delta << endl;
        }
        if (delta > y_pogr) {
            y_pogr = delta;
        }
        x_cur += pogr_otr;
    }
    out6.close();
    vector<double>().swap(A);
    vector<double>().swap(B);
    vector<double>().swap(C);
    vector<double>().swap(F);
    vector<double>().swap(alfa);
    vector<double>().swap(betta);
    vector<double>().swap(h);
    vector<SplineTuple>().swap(spline_value);
    return y_pogr;
}


void task6_main(int n0=5807) {
    int best_count = 0, i = 5800;
    double curr_delta = 100;
    cout  << "Интерполяция сплайнами: " << endl;
    while (curr_delta > (2 * 1e-4)) {
        vector<double> x(i + 1), y(i + 1);
        nodeFillEquals(x, y, i);
        curr_delta = buildSpline(x, y);
        best_count = i;
        i += 1;
        vector<double>().swap(x);
        vector<double>().swap(y);
        cout << i << " " << curr_delta << endl;
    }
//    cout << "Количество сплайнов: " << best_count << endl;
//    vector<double> x(n0+1), y(n0+1);
//    nodeFillEquals(x, y, n0);
//    cout  << "Интерполяция сплайнами: " << buildSpline(x, y) << endl;
    system("python D:/5sem/numerical/practice/labs/Lab1/src/plot/plot_6.py");
}