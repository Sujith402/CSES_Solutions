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

// dp1[v] => number of matches in subtree rooted at v if vertex v is included
// dp2[v] => number of matches in subtree rooted at v if vertex v is not included
vector<int> dp1, dp2;

pair<int, int> dfs(int v, vector<vector<int>>& graph, int p) {
    pair<int, int> out(0, v);
    for (auto u : graph[v]) {
        if (u != p) {
            auto a = dfs(u, graph, v);
            if (a.first + 1 > out.first) {
                out.first = a.first + 1;
                out.second = a.second;
            }
        }
    }
    // cout << out.first << " " << out.second << "\n";
    return out;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<vector<int>> graph(n + 1), rev_graph(n + 1);

    int v, u;
    for (int i = 1; i < n; i++) {
        cin >> v >> u;
        graph[v].push_back(u);
        graph[u].push_back(v);
    }

    dp1.assign(n + 1, 0);
    dp2.assign(n + 1, 0);

    int root = dfs(1, graph, -1).second;
    int res = dfs(root, graph, -1).first;

    // debug(root);
    // debug(dp1);
    // debug(dp2);

    cout << res << "\n";
}
