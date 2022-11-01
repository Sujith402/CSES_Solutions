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
    string s;
    cin >> s;

    // Validate current sequence
    // find x= no. of open and y= no. of closed
    // Calculate properly
    int val = 0, x = 0, y = 0;
    bool poss = true;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') {
            val++;
            x++;
        } else {
            val--;
            y++;
        }
        if (val < 0) {
            poss = false;
            break;
        }
    }

    if (!poss || n % 2 == 1 || x > n / 2) {
        cout << "0\n";
        return 0;
    }

    vector<int> fact(2 * n + 1), modInvfact(2 * n + 1);
    fact[0] = modInvfact[0] = 1;
    for (int i = 1; i <= 2 * n; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
        // FLT
        modInvfact[i] = binpow(fact[i], MOD - 2, MOD);
    }

    int ans = 1;
    // val == k
    // Ans is according to a convolution on the Catalan number

    int k = val;
    int nprime = (n - s.size() - k) / 2;
    // cout << nprime << " " << k << "\n";

    ans = fact[nprime * 2 + k];
    ans = (ans * (k + 1)) % MOD;
    ans = (ans * modInvfact[nprime]) % MOD;
    ans = (ans * modInvfact[nprime + k]) % MOD;
    ans = (ans * binpow(nprime + k + 1, MOD - 2, MOD)) % MOD;

    cout << ans << "\n";
}
