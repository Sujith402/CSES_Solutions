#include "bits/stdc++.h"
using namespace std;
#define int long long

#ifdef local
#include "../debugger.h"
#else
#define debug(...) 42;
#endif

const int MOD = 1e9 + 7;
const int K = 25;

long long binpow(long long a, long long b, int m) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) {
            res = (res * a) % m;
        }
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

int modInv(int a) {
    return binpow(a, MOD - 2, MOD);
}

int GP(int a, int n) {
    return ((binpow(a, n + 1, MOD) - 1 + MOD) % MOD * binpow(a - 1, MOD - 2, MOD)) % MOD;
}

// int sumToN(int n) {
//     return (((n) * (n + 1)) % MOD * modInv(2)) % MOD;
// }

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    int num_of_div = 1;
    int sum_of_div = 1;
    int prod_of_div = 1;
    int sum_of_k = 0;

    vector<pair<int, int>> v(n);

    int p, k;
    for (int i = 0; i < n; i++) {
        cin >> p >> k;
        v[i].first = p;
        v[i].second = k;

        num_of_div = (num_of_div * (k + 1)) % MOD;
        sum_of_div = (sum_of_div * GP(p, k)) % MOD;
        // sum_of_k += k + 1;
    }

    // ! TODO
    // prod^2 = n^(num_of_div)
    // prod = (p1^k1 * p2^k2 * ... * pn^kn)^(num_of_div/2);
    // if one odd exponent, change gamma
    // else change every exponent to exp/2 when multiplying
    // Remember: modInv(2) does not work as 2,MOD-1 are not co-prime
    prod_of_div = 1;
    int posOdd = -1;
    for (int i = 0; i < n; i++) {
        if (v[i].second % 2 == 1) {
            posOdd = i;
            break;
        }
    }
    if (posOdd != -1) {
        // dealing with powers so mod-1
        // gamma = (num_of_div / 2) % (MOD-1)
        int gamma = 1;
        for (int i = 0; i < n; ++i) {
            if (i == posOdd) {
                gamma = (gamma * ((v[i].second + 1) / 2)) % (MOD - 1);
            } else
                gamma = (gamma * (v[i].second + 1)) % (MOD - 1);
        }
        for (int i = 0; i < n; i++) {
            prod_of_div = (prod_of_div * binpow(v[i].first, (v[i].second * gamma) % (MOD - 1), MOD)) % MOD;
        }
    } else {
        int gamma = 1;
        for (int i = 0; i < n; ++i) {
            gamma = (gamma * (v[i].second + 1)) % (MOD - 1);
        }
        for (int i = 0; i < n; i++) {
            prod_of_div = (prod_of_div * binpow(v[i].first, ((v[i].second / 2) * gamma) % (MOD - 1), MOD)) % MOD;
        }
    }

    cout << num_of_div << "\n";
    cout << sum_of_div << "\n";
    cout << prod_of_div << "\n";
}
