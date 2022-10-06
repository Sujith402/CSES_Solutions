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

void dfs(int v, vector<vector<int>>& graph, int p) {
    for (auto u : graph[v]) {
        if (u != p) {
            dfs(u, graph, v);
            dp2[v] += max(dp1[u], dp2[u]);
        }
    }

    for (auto u : graph[v]) {
        // dp1[v] is dependent on dp2[v]
        // dp2[u] + 1 => count edge [v,u]
        // dp2[v] - max(dp1[u], dp2[u]) =>  sum( max(dp1[k], dp2[k]) ) for all children of v, where k!=u
        if (u != p)
            dp1[v] = max(dp1[v], dp2[u] + 1 + dp2[v] - max(dp1[u], dp2[u]));
    }
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

    int root = 1;
    for (int i = 1; i <= n; i++) {
        if (graph[i].size() == 1) {
            root = i;
            break;
        }
    }

    dp1.assign(n + 1, 0);
    dp2.assign(n + 1, 0);

    dfs(root, graph, -1);

    // debug(root);
    // debug(dp1);
    // debug(dp2);

    cout << max(dp1[root], dp2[root]) << "\n";
}
