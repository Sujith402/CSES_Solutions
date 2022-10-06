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

int bfs(int start, vector<vector<int>> graph) {
    int n = graph.size() - 1;

    queue<int> q;
    vector<bool> visited(n + 1, 0);
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        for (auto x : graph[curr]) {
            if (!visited[x]) {
                q.push(x);
                visited[x] = true;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (i == start) continue;
        if (!visited[i]) {
            return i;
        }
    }

    return 0;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n + 1), rev_graph(n + 1);
    int u, v;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        graph[u].push_back(v);
        rev_graph[v].push_back(u);
    }

    int c;
    if ((c = bfs(1, graph)) == 0) {
        if ((c = bfs(1, rev_graph)) == 0)
            cout << "YES\n";
        else {
            cout << "NO\n";
            cout << c << " " << 1 << "\n";
        }
    } else {
        cout << "NO\n";
        cout << 1 << " " << c << "\n";
    }
}
