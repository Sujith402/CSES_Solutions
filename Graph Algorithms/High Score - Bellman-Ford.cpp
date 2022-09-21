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

struct edge {
    int in, out, weight;
};

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<int> dist(n + 1, M);
    vector<int> marked(n + 1, 0);
    vector<edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].in >> edges[i].out >> edges[i].weight;
        edges[i].weight = -edges[i].weight;
    }
    dist[1] = 0;
    marked[1] = marked[n] = 1;

    // calculate shortest paths
    for (int i = 1; i <= n - 1; i++) {
        for (int j = 0; j < m; j++) {
            auto u = edges[j].in, v = edges[j].out, w = edges[j].weight;
            if (dist[u] != M) {
                dist[v] = min(dist[v], dist[u] + w);
            }
        }
    }

    debug(dist);

    vector<vector<int>> graph(n + 1);
    for (int j = 0; j < m; j++) {
        graph[edges[j].out].push_back(edges[j].in);
    }
    stack<int> s;
    vector<int> back(n + 1, -1), visited(n + 1, 0);
    s.push(n);
    while (!s.empty()) {
        int curr = s.top();
        s.pop();
        for (auto node : graph[curr]) {
            if (!visited[node]) {
                back[node] = curr;
                s.push(node);
                visited[node] = 1;
            }
            if (node == 1 || node == n) {
                int c = curr;
                while (c != n) {
                    marked[c] = 1;
                    c = back[c];
                }
            }
        }
    }
    debug(graph);
    debug(visited);
    debug(back);

    vector<int> new_dist(dist);
    // check for negative cycles
    for (int j = 0; j < m; j++) {
        auto u = edges[j].in, v = edges[j].out, w = edges[j].weight;
        if (new_dist[u] != M) {
            new_dist[v] = min(new_dist[v], new_dist[u] + w);
        }
    }

    debug(new_dist);
    debug(marked);
    bool flag = true;
    for (int i = 1; i <= n; i++) {
        if (marked[i] && new_dist[i] < dist[i]) {
            flag = false;
        }
    }

    if (flag) {
        cout << -dist[n] << "\n";
    } else {
        cout << "-1\n";
    }
}