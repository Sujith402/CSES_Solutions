#include "bits/stdc++.h"
using namespace std;
#define int long long

#ifdef local
#include "../debugger.h"
#else
#define debug(...) 42;
#endif

const int MOD = 1e9 + 7;
const int M = 1e6 + 1;
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

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;

    // Calculating (a!)/(b!*(a-b)!) using Modular Inverse
    vector<int> fact(M);
    fact[0] = 1;
    for (int i = 1; i < M; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }

    vector<int> modInvFact(M);
    modInvFact[0] = 1;
    for (int i = 1; i < M; i++) {
        modInvFact[i] = binpow(fact[i], MOD - 2, MOD);
    }

    cin >> n;
    int a, b;
    while (n--) {
        cin >> a >> b;
        cout << ((fact[a] * modInvFact[b]) % MOD * modInvFact[a - b]) % MOD << "\n";
    }
}
