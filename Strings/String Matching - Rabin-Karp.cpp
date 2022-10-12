#include "bits/stdc++.h"
using namespace std;
#define int long long

#ifdef local
#include "../debugger.h"
#else
#define debug(...) 42;
#endif

const int MOD = 1e9 + 9;

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    string s, t;
    cin >> t;
    cin >> s;

    int p = 31;
    int S = s.size(), T = t.size();

    // Used for calculating the polynomial rolling hash for strings
    vector<int> p_pow(max(S, T));
    p_pow[0] = 1;
    for (int i = 1; i < (int)p_pow.size(); i++)
        p_pow[i] = (p_pow[i - 1] * p) % MOD;

    // calculate hash for all prefixes of text
    vector<int> h(T + 1, 0);
    for (int i = 0; i < T; i++)
        h[i + 1] = (h[i] + (t[i] - 'a' + 1) * p_pow[i]) % MOD;

    // calculate hash for pattern
    int h_s = 0;
    for (int i = 0; i < S; i++)
        h_s = (h_s + (s[i] - 'a' + 1) * p_pow[i]) % MOD;

    // why does this work?
    // with a substring of length equal to the text length, it is guaranteed
    // that a collision can't occur i.e. if hashes are equal, the strings are
    // also equal
    vector<int> occurences;
    for (int i = 0; i + S - 1 < T; i++) {
        int curr_hash = (h[i + S] - h[i] + MOD) % MOD;
        if (curr_hash == (h_s * p_pow[i]) % MOD)
            occurences.push_back(i);
    }

    cout << occurences.size() << "\n";
}
