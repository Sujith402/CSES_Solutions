#include "bits/stdc++.h"
using namespace std;
#define int long long
//#define debug(x) cout << #x << " : " << x << " "

#ifdef local
#include "../debugger.h"
#else
#define debug(...) 42;
#endif
const int M = 1e14;
const int MOD = 1e9 + 7;

// floor(log2(n)) = 30 where n <= 2*1e5
const int MAX = 30;

int lift(int n, int k, vector<vector<int>>& par) {
    int out = n;
    int c = 0;
    while (k != 0) {
        if (k & 1) {
            out = par[c][out];
            // cout << c << " " << out << "\n";
        }
        k /= 2;
        c++;
    }
    return out;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    vector<vector<int>> parents(MAX, vector<int>(n + 1, -1));
    for (int i = 1; i <= n; i++)
        cin >> parents[0][i];

    for (int k = 1; k < MAX; k++) {
        for (int i = 1; i <= n; i++) {
            if (parents[k - 1][i] != -1)
                parents[k][i] = parents[k - 1][parents[k - 1][i]];
        }
    }

    // debug(parents);

    while (q--) {
        int node, k;
        cin >> node >> k;
        cout << lift(node, k, parents) << "\n";
    }
}
