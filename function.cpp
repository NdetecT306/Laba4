#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <locale>
using namespace std;
double f(double x) {
    return cos(x + 0.3) - x * x;
}
double fstrih(double x) {
    return -sin(x + 0.3) - 2 * x;
}
double Newton(double x0, double e, int iter) {
    double xn = x0;
    double xn1;
    int N = 0;
    cout << "--------------------------------------------------" << endl;
    cout << "N" << "  \t  " << "xn" << " \t\t " << " xn + 1 " << "\t" << "xn + 1 - xn" << endl;
    cout << "--------------------------------------------------" << endl;
    do {
        xn1 = xn - f(xn) / fstrih(xn);
        N++;
        cout << N << "\t" << fixed << setprecision(6) << xn<< "\t" << xn1 << "\t"<< xn1 - xn << endl;
        if (fabs(xn1 - xn) < e) {
            return xn1;
        }
        if (N > iter) {
            return NAN;
        }
        xn = xn1;
    } while (true);
}
double Chord(double a, double b, double e, int iter) {
    double xn = a;
    double xn1;
    int N = 0;
    cout << "--------------------------------------------------" << endl;
    cout << "N" << "  \t  " << "xn" << " \t\t " << " xn + 1 " << "\t" << "xn + 1 - xn" << endl;
    cout << "--------------------------------------------------" << endl;
    do {
        xn1 = a - f(a) * (b - a) / (f(b) - f(a));
        N++;
        cout << N << "\t" << fixed << setprecision(6) << xn << "\t" << xn1<< "\t"  << xn1 - xn  << endl;
        if (fabs(xn1 - xn) < e) {
            return xn1;
        }
        if (f(a) * f(xn1) < 0) {
            b = xn1;
        }
        else {
            a = xn1;
        }
        if (N > iter) {
            return NAN;
        }
        xn = xn1;
    } while (true);
}
double Broyden(double x0, double e, int iter) {
    double xn = x0;
    double xn1;
    double c = fstrih(x0);
    int N = 0;
    if (fabs(c) < 1e-10) {
        return NAN;
    }
    cout << "--------------------------------------------------" << endl;
    cout << "N" << "  \t  " << "xn" << " \t\t " << " xn + 1 " << "\t" << "xn + 1 - xn" << endl;
    cout << "--------------------------------------------------" << endl;
    for (N = 1; N <= iter; ++N) {
        xn1 = xn - f(xn) / c;
        cout << N << "\t" << fixed << setprecision(6) << xn << "\t" << xn1 << "\t" << xn1 - xn << endl;
        if (fabs(xn1 - xn) < e) {
            
            return xn1;
        }
        double s = xn1 - xn;
        double y = f(xn1) - f(xn);
        c = c + (y - c * s) / (s * s); 
        xn = xn1;
    }
    return NAN;
}
int main() {
    setlocale(LC_ALL, "rus");
    double e = 0.00001;
    int iter = 100;
    double step = 0.01;
    vector<double> intervals = { -1.0, 0.7 };
    vector<double> rootsNewton;
    vector<double> rootsChord;
    vector<double> rootsBroyden;
    cout << "1) МЕТОД НЬЮТОНА" << endl;
    for (double x0 : intervals) {
        cout << endl << "x0 = " << x0 << endl << endl;
        double root = Newton(x0, e, iter);
        if (!isnan(root)) {
            rootsNewton.push_back(root);
        }
    }
    cout << endl << endl;
    cout << "2) МЕТОД ХОРД" << endl;
    for (double x0 : intervals) {
        cout << endl << "x0 = " << x0 << endl << endl;
        double a = x0;
        double b = x0 + step;
        double root = Chord(a, b, e, iter);
        if (!isnan(root)) {
            rootsChord.push_back(root);
        }
    }
    cout << endl << endl;
    cout << "3) МЕТОД БРОЙДЕНА" << endl;
    for (double x0 : intervals) {
        cout << endl << "x0 = " << x0 << endl << endl;
        double root = Broyden(x0, e, iter);
        if (!isnan(root)) {
            rootsBroyden.push_back(root);
        }
    }
    cout << "\nМетод Ньютона:" << endl;
    if (rootsNewton.empty()) {
        cout << "Корни не найдены." << endl;
    }
    else {
        sort(rootsNewton.begin(), rootsNewton.end());
        for (const auto i : rootsNewton) {
            cout << "x" << " = " << fixed << setprecision(6) << i << endl;
        }
    }
    cout << "\nМетод Хорд:" << endl;
    if (rootsChord.empty()) {
        cout << "Корни не найдены." << endl;
    }
    else {
        sort(rootsChord.begin(), rootsChord.end());
        for (const auto i : rootsChord) {
            cout << "x" << " = " << fixed << setprecision(6) << i << endl;
        }
    }
    cout << "\nМетод Бройдена:" << endl;
    if (rootsBroyden.empty()) {
        cout << "Корни не найдены." << endl;
    }
    else {
        sort(rootsBroyden.begin(), rootsBroyden.end());
        for (const auto i : rootsBroyden) {
            cout << "x" << " = " << fixed << setprecision(6) << i << endl;
        }
    }
    cout << endl;
    return 0;
}
