#include <iostream>
using namespace std;

long long power(long long base, int exp) {
    long long res = 1;
    for (int i = 0; i < exp; i++) {
        res *= base;
    }
    return res;
}

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main() {
    int a, b;
    cin >> a >> b;

    if (b <= 1) {
        cout << "infinity";
        return 0;
    }

    long long num = 0;
    long long den = power(b - 1, a + 1);

    for (int k = 0; k <= a; k++) {
        num += power(b - 1, k);
    }

    long long g = gcd(num, den);
    num /= g;
    den /= g;

    cout << num << "/" << den;

    return 0;
}
