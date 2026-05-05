#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    long long pavel = 0;
    long long vika = 0;

    int pos = 0;
    int lastMove = 0;
    bool pavelTurn = true;

    while (pos < n) {
        long long bestSum = -4000000000000000000LL;
        int bestCount = 1;

        long long currentSum = 0;
        int maxCount = min(m, n - pos);

        for (int count = 1; count <= maxCount; count++) {
            currentSum += a[pos + count - 1];

            if (count == lastMove) {
                continue;
            }

            if (currentSum > bestSum) {
                bestSum = currentSum;
                bestCount = count;
            }
        }

        if (pavelTurn) {
            pavel += bestSum;
        } else {
            vika += bestSum;
        }

        pos += bestCount;
        lastMove = bestCount;
        pavelTurn = !pavelTurn;
    }

    if (pavel > vika) {
        cout << 1 << endl;
    } else {
        cout << 0 << endl;
    }

    return 0;
}
