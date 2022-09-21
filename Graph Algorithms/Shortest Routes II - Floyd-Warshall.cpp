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

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> graph(n + 1, vector<int>(n + 1, M));
    int x, y, w;
    for (int i = 0; i < m; i++) {
        cin >> x >> y >> w;
        graph[x][y] = min(graph[x][y], w);
        graph[y][x] = min(graph[y][x], w);
    }
    for (int i = 1; i <= n; i++) {
        graph[i][i] = 0;
    }

    vector<vector<int>> dp(graph);
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
            }
        }
    }

    while (q--) {
        cin >> x >> y;
        cout << (dp[x][y] == M ? -1 : dp[x][y]) << "\n";
    }
}