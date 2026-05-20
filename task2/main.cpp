#include <iostream>
#include <vector>
#include <numeric>
#include <cstdlib>
#include <ctime>

using namespace std;

using ulong = unsigned long;

ulong bitLength(ulong n) {
    ulong bits = 0;
    while (n > 0) {
        ++bits;
        n >>= 1;
    }
    return bits;
}

ulong modPow(ulong a, ulong power, ulong mod) {
    ulong result = 1;
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

vector<ulong> sieveEratosthenes(ulong limit) {
    vector<bool> isPrime(limit + 1, true);

    isPrime[0] = false;
    isPrime[1] = false;

    for (ulong p = 2; p * p <= limit; ++p) {
        if (isPrime[p]) {
            for (ulong i = p * p; i <= limit; i += p) {
                isPrime[i] = false;
            }
        }
    }

    vector<ulong> primes;

    for (ulong i = 2; i <= limit; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}

void generateF(int bits, const vector<ulong>& primes, ulong& F, vector<ulong>& qList) {
    int targetBits = bits / 2 + 1;

    F = 1;
    qList.clear();

    while ((int)bitLength(F) < targetBits) {
        ulong q = primes[rand() % primes.size()];

        if ((int)bitLength(F * q) > targetBits) {
            continue;
        }

        F *= q;

        bool exists = false;
        for (ulong x : qList) {
            if (x == q) {
                exists = true;
                break;
            }
        }

        if (!exists) {
            qList.push_back(q);
        }
    }
}

bool pocklingtonTest(ulong n, const vector<ulong>& qList, int t) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;

    vector<ulong> bases;

    while ((int)bases.size() < t) {
        ulong a = 2 + rand() % (n - 3);

        bool exists = false;
        for (ulong x : bases) {
            if (x == a) {
                exists = true;
                break;
            }
        }

        if (!exists) {
            bases.push_back(a);
        }
    }

    for (ulong a : bases) {
        if (modPow(a, n - 1, n) != 1) {
            return false;
        }
    }

    for (ulong q : qList) {
        bool passedForQ = false;

        for (ulong a : bases) {
            ulong value = modPow(a, (n - 1) / q, n);

            if (value == 0) {
                continue;
            }

            if (gcd(value - 1, n) == 1) {
                passedForQ = true;
                break;
            }
        }

        if (!passedForQ) {
            return false;
        }
    }

    return true;
}

bool generateCandidate(int bits, const vector<ulong>& primes, ulong& n, ulong& F, vector<ulong>& qList) {
    generateF(bits, primes, F, qList);

    ulong fBits = bitLength(F);
    ulong rBits = fBits - 1;

    ulong leftR = 1UL << (rBits - 1);
    ulong rightR = (1UL << rBits) - 1;

    for (int attempt = 0; attempt < 1000; ++attempt) {
        ulong R = leftR + rand() % (rightR - leftR + 1);

        if (R % 2 == 1) {
            ++R;
        }

        if (R > rightR) {
            R -= 2;
        }

        if (R == 0 || R >= F) {
            continue;
        }

        if (gcd(R, F) != 1) {
            continue;
        }

        n = R * F + 1;

        if ((int)bitLength(n) != bits) {
            continue;
        }

        if (F * F <= n) {
            continue;
        }

        return true;
    }

    return false;
}

int main() {
    srand(time(0));

    int bits;

    cout << "Введите количество бит: ";
    cin >> bits;

    if (bits < 4 || bits > 30) {
        cout << "Ошибка: количество бит должно быть от 4 до 30" << endl;
        return 0;
    }

    vector<ulong> primes = sieveEratosthenes(499);

    int found = 0;
    int rejected = 0;

    cout << "\nРезультаты теста Поклингтона\n";
    cout << "№\tЧисло n\t\tF\t\tРезультат\tRejected\n";

    while (found < 10) {
        ulong n;
        ulong F;
        vector<ulong> qList;

        if (!generateCandidate(bits, primes, n, F, qList)) {
            ++rejected;
            continue;
        }

        bool firstCheck = pocklingtonTest(n, qList, 1);
        bool secondCheck = false;

        if (firstCheck) {
            secondCheck = pocklingtonTest(n, qList, 2);
        }

        if (firstCheck && secondCheck) {
            ++found;

            cout << found << "\t"
                 << n << "\t\t"
                 << F << "\t\t"
                 << "true\t\t"
                 << rejected << endl;

            rejected = 0;
        } else {
            ++rejected;
        }
    }

    return 0;
}

