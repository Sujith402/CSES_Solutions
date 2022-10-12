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

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    // jump[i][j] => jump from node j to 2^ith parent
    vector<vector<int>> jump(K, vector<int>(n + 1, -1));
    for (int i = 2; i <= n; i++) {
        cin >> jump[0][i];
    }

    for (int k = 1; k < K; k++) {
        for (int j = 1; j <= n; j++) {
            if (jump[k - 1][j] != -1) {
                jump[k][j] = jump[k - 1][jump[k - 1][j]];
            }
        }
    }

    while (q--) {
        int node, k;
        bool done = false;
        cin >> node >> k;
        for (int i = 0; k != 0 && i < K; i++) {
            if (k % 2) {
                if (jump[i][node] == -1) {
                    cout << "-1\n";
                    done = true;
                    break;
                }
                node = jump[i][node];
            }
            k /= 2;
        }
        if (!done)
            cout << node << "\n";
    }
}
