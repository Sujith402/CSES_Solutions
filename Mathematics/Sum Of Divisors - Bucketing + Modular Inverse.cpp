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

long long binpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) {
            res = (res * a) % MOD;
        }
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

// modular inverse
// given MOD is prime, a^(-1) === a^(MOD-2) mod MOD
// This follows from Fermat's Little Theorem
// Look into modular inverse a little more
int sumToN(int n) {
    return (((n % MOD * ((n - 1) % MOD)) % MOD) * (binpow(2, MOD - 2))) % MOD;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;

    // ans becomes (n + n/2 + n/3 + ... + 1)
    // how to calculate this in less than O(n) time?
    // n/i forms blocks for contiguous values of i
    // how to find these blocks?
    // after finding the blocks, calculate contiguous sum and multiply by block length

    int i = 1;
    int ans = 0;
    while (i <= n) {
        int curr = n / i;
        int next = n / curr + 1;
        // int next_mod = next % MOD;

        // int val = (((next_mod * ((next_mod - 1) % MOD)) / 2) % MOD - (((i % MOD) * (((i % MOD) - 1) % MOD)) / 2) % MOD) % MOD;
        int val = (sumToN(next) - sumToN(i) + MOD) % MOD;
        ans = (ans + (((curr % MOD) * val) % MOD)) % MOD;
        i = next;
    }

    cout << ans << "\n";
}
