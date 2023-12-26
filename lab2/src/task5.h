
const double ANS=0.268487278503810;

double f(double x) {
    return x * x * acos(0.9 * x);
}

double f_2(double x) {
    return 2 * acos(0.9 * x) - (3.6 * x) / sqrt(-0.81 * x * x + 1) - (0.792 * x * x * x) / pow(-0.81 * x * x + 1, 1.5);
}

void MakeGrid(int count, double& a, double& b, vector<double>& X, vector<double>& Y) {
    if (X.size() != count) {
        X.resize(count);
        Y.resize(count);
    }

    for (int i = 0; i < count; i++) {
        X[i] = a + (b - a) * i / (double)(count);
        Y[i] = f(X[i]);
    }
}

void OptimalTrapez(int count, double a, double b, double& maxD, ostream& file = cout, int paramToCout = 0) {
    vector<double> X;
    vector<double> Y;


    vector<double> B(count+1);
    vector<double> ai;
    vector <double> bi(count);

    for (int i = 0; i < count+1; i++)
    {
        B[i] = (b - a)*i / count;
    }
    for (int i = 0; i < count; i++)
    {
        bi[i] = B[i + 1] - B[i];
    }
    int gridSizeForAi = 2e3;
    MakeGrid(gridSizeForAi, a, b, X, Y);
    // MAKING AI
    double buf = 0.0;
    double maxPart = 0.0;
    int areaofA = 0;
    for (int i = 0; i < gridSizeForAi; i++) {
        buf = f_2(X[i]);
        if (maxPart < abs(buf)) maxPart = abs(buf);
        if (i < gridSizeForAi-2)
        {
            if (X[i + 1] > b / (double)(count) * (areaofA + 1))
            {
                ai.push_back(maxPart);
                maxPart = 0.0;
                areaofA++;
            }
        }
        if (i == gridSizeForAi - 1) {
            ai.push_back(maxPart);
        }
    }
    //

    //searching lamda:
    double lambda = pow(1e-2,1.5) * 4 * sqrt(3);
    double del = 0;
    for (int i = 0; i < count; i++) {
        del += pow(bi[i],1.5) * sqrt(ai[i]);
    }
    lambda *= del;
    vector<double> Ni;
    int buffer_NI = 0;
    for (int i = 0; i < count; i++) {
        buffer_NI = round((bi[i] * pow(ai[i] / 6 / lambda, 1. / 3.)));
        Ni.push_back((buffer_NI != 0) ? buffer_NI : 1);
    }
    //cout << Ni[0];

    //H[i];
    vector<double> Hl;
    for (int i = 0; i < count; i++) {
        Hl.push_back(bi[i] / Ni[i]);
    }
    //cout << Hl[0];
    vector <double> S;
    double local_sum = 0;
    int count_of_points = 0;
    ofstream file_To_Y("task5.txt");

    for (int i = 1; i < B.size(); i++) {
        int j = 1;
        local_sum = f(B[i - 1]) / 2;
        file_To_Y << f(B[i - 1]) / 2 << endl;
        file << B[i - 1] << endl;
        while ((B[i - 1] + j * Hl[i - 1]) < B[i]) {
            file << B[i - 1] + j * Hl[i - 1] << endl;
            file_To_Y << f(B[i - 1] + j * Hl[i - 1]) << endl;
            local_sum += f(B[i - 1] + j * Hl[i - 1]);
            j++;
        }
        count_of_points += j;
        local_sum += f(B[i]) / 2;
        //cout << Hl[i - 1] <<" " << Ni[i - 1] << endl;
        S.push_back(local_sum * Hl[i - 1]);
    }
    file_To_Y << f(B[B.size() - 1]) / 2 << endl;
    file << B[B.size() - 1];
    double sum = 0;
    for (int i = 0; i < S.size(); i++) {
        // cout << S[i] << endl;
        sum += S[i];
    }
    cout <<"Количество :" << count_of_points << "\nпогрешность:" << abs(sum - ANS) << endl;
}

void task5_main() {
    ofstream fileToCout;
    fileToCout.open("OptTrapez.txt");
    double maxD = 100000;
    for (int i = 22; i < 23; i++) {
        OptimalTrapez(i, 0, 1, maxD,fileToCout,1);
    }
}