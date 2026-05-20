
#include <iostream>
#include <vector>

using namespace std;

using ulong = unsigned long;

ulong gcdul(ulong a, ulong b) {
    while (b != 0) {
        ulong t = a % b;
        a = b;
        b = t;
    }

    return a;
}

ulong powul(ulong base, int exp) {
    ulong result = 1;

    for (int i = 0; i < exp; ++i) {
        result *= base;
    }

    return result;
}

vector<vector<ulong>> getEulerianNumbers(int maxA) {
    vector<vector<ulong>> e(maxA + 1, vector<ulong>(maxA + 1, 0));

    e[0][0] = 1;

    for (int n = 1; n <= maxA; ++n) {
        for (int k = 0; k < n; ++k) {
            e[n][k] = (k + 1) * e[n - 1][k];

            if (k > 0) {
                e[n][k] += (n - k) * e[n - 1][k - 1];
            }
        }
    }

    return e;
}

int main() {
    int a;
    int bInput;

    cout << "Введите a и b: ";
    cin >> a >> bInput;

    if (a < 1  a > 10  bInput < 1 || bInput > 10) {
        cout << "Ошибка: a и b должны быть от 1 до 10" << endl;
        return 0;
    }

    if (bInput == 1) {
        cout << "infinity" << endl;
        return 0;
    }

    ulong b = static_cast<ulong>(bInput);

    vector<vector<ulong>> e = getEulerianNumbers(10);

    ulong numerator = 0;
    ulong denominator = powul(b - 1, a + 1);

    for (int k = 0; k < a; ++k) {
        numerator += e[a][k] * powul(b, a - k);
    }

    ulong g = gcdul(numerator, denominator);

    cout << numerator / g << "/" << denominator / g << endl;

    return 0;
}