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

vector<int> topological_sort(vector<vector<int>> graph) {
    int n = graph.size() - 1;
    vector<int> dependents(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int x : graph[i]) {
            dependents[x]++;
        }
    }

    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (dependents[i] == 0)
            q.push(i);
    }

    vector<int> out;
    while (!q.empty()) {
        int node = q.front();
        out.push_back(node);
        q.pop();
        for (auto k : graph[node]) {
            dependents[k]--;
            if (dependents[k] == 0) {
                q.push(k);
            }
        }
    }

    return out;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n + 1), rev_graph(n + 1);
    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        graph[a].push_back(b);
        rev_graph[b].push_back(a);
    }

    vector<int> dp(n + 1);
    dp[1] = 1;

    vector<int> order = topological_sort(graph);

    for (int i = 0; i < n; i++) {
        for (auto v : rev_graph[order[i]]) {
            dp[order[i]] += dp[v];
            dp[order[i]] %= MOD;
        }
    }

    cout << dp[n] << "\n";
}
