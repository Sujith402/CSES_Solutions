#include "bits/stdc++.h"
using namespace std;
#define int long long

#ifdef local
#include "../debugger.h"
#else
#define debug(...) 42;
#endif

const int MOD = 1e9 + 7;
const int M = 2e6 + 1;
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

    int n;
    cin >> n;

    int ans = 0;
    // ans => no. of ways to distribute gifts - {no. of ways to distribute such that at least one connection is to same person}
    // second term is calculated using inclusion-exclusion
    // sum over k:1->n ((-1)^(k+1)*(nCk)*(n-k)!)
    int comb = 1;
    for (int k = 1; k <= n; k++) {
        comb = ((comb * (n - k + 1)) % MOD * binpow(k, MOD - 2, MOD)) % MOD;
        int val = ((comb * fact[n - k]) % MOD) * (k % 2 == 0 ? -1 : 1);
        ans = (ans + val + MOD) % MOD;
    }
    // bad ways is now in ans
    // good ways => n! - ans
    ans = (fact[n] - ans + MOD) % MOD;

    cout << ans << "\n";
}
