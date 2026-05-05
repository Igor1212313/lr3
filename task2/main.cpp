#include <iostream>
using namespace std;

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

long long modPow(long long a, long long power, long long mod) {
    long long result = 1;
    a %= mod;

    while (power > 0) {
        if (power % 2 == 1) {
            result = (result * a) % mod;
        }

        a = (a * a) % mod;
        power /= 2;
    }

    return result;
}

bool isPrimeSimple(long long n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }

    return true;
}

bool pocklingtonTest(long long n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;

    long long q = n - 1;

    for (long long p = 2; p * p <= q; p++) {
        if (q % p == 0 && isPrimeSimple(p)) {
            long long a = 2;

            if (modPow(a, n - 1, n) == 1 &&
                gcd(modPow(a, (n - 1) / p, n) - 1, n) == 1) {
                return true;
            }
        }
    }

    return isPrimeSimple(n);
}

int main() {
    long long n;

    cout << "Введите число N: ";
    cin >> n;

    if (pocklingtonTest(n)) {
        cout << "Число простое" << endl;
    } else {
        cout << "Число составное" << endl;
    }

    return 0;
}
