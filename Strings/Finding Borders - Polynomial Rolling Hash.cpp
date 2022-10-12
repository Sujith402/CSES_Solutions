#include "bits/stdc++.h"
using namespace std;
#define int long long

#ifdef local
#include "../debugger.h"
#else
#define debug(...) 42;
#endif

const int MOD = 1e9 + 7;

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin >> s;

    int p = 31;
    int n = s.size();
    vector<int> p_pow(n);
    p_pow[0] = 1;
    for (int i = 1; i < n; i++)
        p_pow[i] = (p_pow[i - 1] * p) % MOD;
    vector<int> h(n + 1);
    for (int i = 0; i < n; i++) {
        h[i + 1] = (h[i] + (s[i] - 'a' + 1) * p_pow[i]) % MOD;
    }
    // debug(p_pow);
    // debug(h);
    int curr_h = 0;
    vector<int> out;
    for (int i = n - 1; i > 0; i--) {
        curr_h = ((curr_h * p) % MOD + (s[i] - 'a' + 1)) % MOD;
        // cout << curr_h << "\n";
        if (curr_h == h[n - i]) {
            out.push_back(n - i);
        }
    }

    for (int x : out) {
        cout << x << " ";
    }
    cout << "\n";
}
