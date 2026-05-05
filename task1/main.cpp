#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double f(double x) {
    if (x >= -7 && x <= -6) {
        return sqrt(1 - pow(x + 6, 2));
    }
    else if (x > -6 && x <= -3) {
        return (-4.0 / 3.0) * x - 7;
    }
    else if (x >= -3 && x <= 2) {
        return -abs(x) + 1;
    }
    else if (x > 2 && x <= 6) {
        return x - 4;
    }
    else if (x > 6 && x <= 7) {
        return 1 + sqrt(1 - pow(x - 6, 2));
    }

    return NAN;
}

int main() {
    double xStart, xEnd, dx;

    cout << "Введите Xнач, Xкон и dx: ";
    cin >> xStart >> xEnd >> dx;

    cout << fixed << setprecision(3);
    cout << "x\t\ty" << endl;

    for (double x = xStart; x <= xEnd + 1e-9; x += dx) {
        double y = f(x);

        if (isnan(y)) {
            cout << x << "\t\t" << "нет значения" << endl;
        } else {
            cout << x << "\t\t" << y << endl;
        }
    }

    return 0;
}
