#include <iostream>
#include <vector>
using namespace std;

long long gcdll(long long a, long long b) {
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a < 0 ? -a : a;
}

long long powll(long long base, int exp) {
    long long result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

vector<vector<long long>> getEulerianNumbers(int maxA) {
    vector<vector<long long>> e(maxA + 1, vector<long long>(maxA + 1, 0));
    e[0][0] = 1;

    for (int n = 1; n <= maxA; n++) {
        for (int k = 0; k < n; k++) {
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
    long long b;

    cout << "Введите a и b: ";
    cin >> a >> b;

    if (b <= 1) {
        cout << "infinity" << endl;
        return 0;
    }

    vector<vector<long long>> e = getEulerianNumbers(15);

    long long numerator = 0;
    long long denominator = powll(b - 1, a + 1);

    for (int k = 0; k < a; k++) {
        numerator += e[a][k] * powll(b, a - k);
    }

    long long g = gcdll(numerator, denominator);

    numerator /= g;
    denominator /= g;

    cout << numerator << "/" << denominator << endl;

    return 0;
}
