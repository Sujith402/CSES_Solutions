#include "bits/stdc++.h"
using namespace std;
#define int long long

#ifdef local
#include "../debugger.h"
#else
#define debug(...) 42;
#endif

const int M = 1e14;
const int MOD = 1e9 + 7;

// lg(10^7) < 25
const int k = 25;

void read(vector<int>& v) {
    for (int i = 0; i < v.size(); i++)
        cin >> v[i];
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    read(v);

    // sparse_table[i][j] is RMQ(i, i + 2^j - 1)
    vector<vector<int>> sparse_table(n, vector<int>(k + 1));
    for (int i = 0; i < n; i++) {
        sparse_table[i][0] = v[i];
    }

    for (int j = 1; j <= k; j++) {
        for (int i = 0; i + (1ll << j) <= n; i++) {
            sparse_table[i][j] = min(sparse_table[i][j - 1], sparse_table[i + (1ll << (j - 1))][j - 1]);
        }
    }

    // lg2[i] => floor(log2(i))
    int lg2[n + 1];
    lg2[1] = 0;
    for (int i = 2; i <= n; i++) {
        lg2[i] = lg2[i / 2] + 1;
    }

    // processing once or twice is immaterial
    // so spilt into two ranges of max length and query
    int l, r;
    while (q--) {
        cin >> l >> r;
        l--, r--;
        int range_log = lg2[r - l + 1];
        cout << min(sparse_table[l][range_log],
                    sparse_table[r - (1ll << range_log) + 1][range_log])
             << "\n";
    }
}
