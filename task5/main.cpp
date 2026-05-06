#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double Tk, Tsr, r, dt, tmax;

    cout << "Введите начальную температуру кофе Tk: ";
    cin >> Tk;

    cout << "Введите температуру окружающей среды Tsr: ";
    cin >> Tsr;

    cout << "Введите коэффициент остывания r: ";
    cin >> r;

    cout << "Введите шаг времени dt: ";
    cin >> dt;

    cout << "Введите максимальное время tmax: ";
    cin >> tmax;

    cout << fixed << setprecision(2);
    cout << "\nВремя\tТемпература\n";

    double t = 0.0;
    double T = Tk;

    while (t <= tmax + 1e-9) {
        cout << t << "\t" << T << endl;

        T = T - r * (T - Tsr) * dt;
        t += dt;
    }

    return 0;
}
