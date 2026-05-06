#include <iostream>
#include <vector>
#include <numeric>
#include <cstdlib>
#include <ctime>

using namespace std;

long long modPow(long long a, long long p, long long mod) {
    long long result = 1;
    a %= mod;

    while (p > 0) {
        if (p % 2 == 1)
            result = (__int128)result * a % mod;

        a = (__int128)a * a % mod;
        p /= 2;
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
    srand(time(0));

    int bits;
    cout << "Введите количество бит: ";
    cin >> bits;

    if (bits < 2 || bits > 30) {
        cout << "Ошибка: количество бит должно быть от 2 до 30" << endl;
        return 0;
    }

    long long left = 1LL << (bits - 1);
    long long right = (1LL << bits) - 1;

    int found = 0;
    int rejected = 0;

    cout << "\nДиапазон: [" << left << "; " << right << "]" << endl;
    cout << "№\tЧисло\tРезультат\tRejected\n";

    while (found < 10) {
        long long n = left + rand() % (right - left + 1);

        if (n % 2 == 0)
            n++;

        if (n > right)
            n -= 2;

        if (pocklingtonTest(n)) {
            found++;
            cout << found << "\t" << n << "\tпростое\t\t" << rejected << endl;
            rejected = 0;
        } else {
            rejected++;
        }
    }

    return 0;
}
