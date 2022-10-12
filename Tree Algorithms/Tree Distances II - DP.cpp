#include "bits/stdc++.h"
using namespace std;
#define int long long

#ifdef local
#include "../debugger.h"
#else
#define debug(...) 42;
#endif

const int MOD = 1e9 + 7;

void dfs(int curr, int p, vector<vector<int>>& graph, vector<pair<int, int>>& dist) {
    for (auto v : graph[curr]) {
        if (v != p) {
            int num_nodes_of_parent = (graph.size() - 2 - dist[v].second);
            int total_sum_of_parent = (dist[curr].first - dist[v].first - dist[v].second - 1);
            // debug(v, curr, num_nodes_of_parent, total_sum_of_parent);
            dist[v].first += num_nodes_of_parent + total_sum_of_parent;
            dfs(v, curr, graph, dist);
        }
    }
}

// calculate max depth of subtree of a particular node
void dfs1(int curr, int p, vector<vector<int>>& graph, vector<pair<int, int>>& dist) {
    for (int u : graph[curr]) {
        if (u != p) {
            dfs1(u, curr, graph, dist);
            dist[curr].first += dist[u].first + (dist[u].second) + 1;
            dist[curr].second += (dist[u].second + 1);
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    int x, y;
    vector<vector<int>> graph(n + 1);
    for (int i = 1; i < n; i++) {
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    // sums[i] => sum of dist to all nodes of subtree, number of nodes in subtree
    vector<pair<int, int>> sums(n + 1, {0, 0});

    dfs1(1, 0, graph, sums);

    debug(sums);

    dfs(1, 0, graph, sums);

    debug(sums);

    for (int i = 1; i <= n; i++) {
        cout << sums[i].first << " ";
    }
    cout << "\n";
}
