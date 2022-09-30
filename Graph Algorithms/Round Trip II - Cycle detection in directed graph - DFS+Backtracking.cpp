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

// Presence of a back edge indicates a cycle in a directed graph
// How do you detect this back edge?
// Implement a recursive dfs that keeps track of the ancestors of the current node
// How do you keep track of this?
// Implement dfs via backtracking;

struct Graph {
    vector<vector<int>> g;
    vector<int> out, p;

    Graph(int n) {
        g.resize(n);
        p = vector<int>(n, -1);
    }

    bool dfs(int u, vector<bool>& visited, vector<bool>& same_subtree) {
        // debug(same_subtree);
        for (auto v : g[u]) {
            // cout << u << " -> " << v << "\n";
            if (!visited[v]) {
                visited[v] = true;
                p[v] = u;
                same_subtree[v] = true;
                if (dfs(v, visited, same_subtree)) {
                    return true;
                };
                same_subtree[v] = false;
            } else if (same_subtree[v]) {
                out.push_back(v);
                for (int n = u; n != v; n = p[n]) {
                    out.push_back(n);
                }
                out.push_back(v);
                reverse(out.begin(), out.end());
                return true;
            }
        }
        return false;
    }
};

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    Graph graph(n + 1);
    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        graph.g[a].push_back(b);
    }

    vector<int> p(n + 1, -1);
    vector<bool> visited(n + 1, 0), same_subtree(n + 1, 0);
    bool done = false;

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            visited[i] = true;
            same_subtree[i] = true;
            if (graph.dfs(i, visited, same_subtree)) {
                cout << graph.out.size() << "\n";
                for (auto x : graph.out) {
                    cout << x << " ";
                }
                cout << "\n";
                done = true;
                break;
            };
            same_subtree[i] = false;
        }
    }

    if (!done) {
        cout << "IMPOSSIBLE\n";
    }
}
