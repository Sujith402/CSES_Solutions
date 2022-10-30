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

inline long long mpow(long long b, long long ex) {
    if (b == 1) return 1;
    long long r = 1;
    while (ex) {
        if (ex & 1) r = (r * b) % MOD;
        ex = ex >> 1;
        b = (b * b) % MOD;
    }
    return r;
}

struct Hash {
    int p;
    int S, T;
    vector<int> p_pow, h_s, mul_inv;
    Hash(string& s) {
        p = 31;
        S = s.size();
        T = s.size() / 2;

        p_pow.resize(S);
        p_pow[0] = 1;
        for (int i = 1; i < (int)p_pow.size(); i++)
            p_pow[i] = (p_pow[i - 1] * p) % MOD;

        // hash[i] = hash(s[0...i])
        h_s.resize(S);
        h_s[0] = (s[0] - 'a' + 1);
        for (int i = 1; i < S; i++) {
            h_s[i] = (h_s[i - 1] + p_pow[i] * (s[i] - 'a' + 1)) % MOD;
        }

        mul_inv.resize(S);
        for (int i = 0; i < S; i++) {
            // multiplicative inverse of x is mpow(x, MOD-2)
            mul_inv[i] = mpow(p_pow[i], MOD - 2);
        }
    }

    int get(int l, int r) {
        if (l == 0) return h_s[r];
        return ((h_s[r] - h_s[l - 1] + MOD) * mul_inv[l]) % MOD;
    }
};

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;
    int n = (int)s.size();

    s = s + s;
    Hash hash(s);

    int k = 0;
    for (int i = 1; i < n; i++) {
        int hi = n - 1, lo = 0;
        while (lo < hi) {
            int mid = (hi + lo) / 2;
            if (hash.get(i, i + mid) == hash.get(k, k + mid)) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }

        if (lo <= n - 1) {
            if (s[i + lo] < s[k + lo]) {
                k = i;
            }
        }
    }

    cout << s.substr(k, n) << "\n";
}
