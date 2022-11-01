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

    int n;
    cin >> n;

    if (n % 2 != 0) {
        cout << 0 << "\n";
        return 0;
    }
    n /= 2;

    // Catalan number
    // 1/(n+1) * 2nCn
    vector<int> fact(2 * n + 1), modInvfact(n + 1);
    fact[0] = modInvfact[0] = 1;
    for (int i = 1; i <= 2 * n; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    for (int i = 1; i <= n; i++) {
        // FLT
        modInvfact[i] = binpow(fact[i], MOD - 2, MOD);
    }

    int ans = 1;
    ans = (ans * fact[2 * n]) % MOD;
    ans = (ans * modInvfact[n]) % MOD;
    ans = (ans * modInvfact[n]) % MOD;
    ans = (ans * binpow(n + 1, MOD - 2, MOD)) % MOD;

    cout << ans << "\n";
}
