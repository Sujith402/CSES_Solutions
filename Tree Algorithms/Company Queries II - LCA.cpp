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

struct LCA {
    vector<vector<int>> p;
    vector<int> d;

    LCA(vector<int> parents, vector<int> depth) : d(depth) {
        int n = parents.size() - 1;
        p.assign(K, vector<int>(n + 1, -1));
        for (int i = 1; i <= n; i++)
            p[0][i] = parents[i];

        init();
    }

    void init() {
        int n = p[0].size() - 1;
        for (int i = 1; i < K; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[i - 1][j] != -1) {
                    p[i][j] = p[i - 1][p[i - 1][j]];
                }
            }
        }
    }

    void walk(int& a, int& b) {
        if (d[a] > d[b])
            swap(a, b);
        int diff = d[b] - d[a];
        int c = 0;
        while (diff) {
            if (diff & 1) {
                b = p[c][b];
            }
            diff /= 2;
            c++;
        }
    }

    int find_LCA(int a, int b) {
        walk(a, b);

        if (a == b) return a;

        for (int k = K - 1; k >= 0; k--) {
            if (p[k][a] != p[k][b]) {
                a = p[k][a];
                b = p[k][b];
            }
        }

        return p[0][a];
    }

    int query(int a, int b) {
        return find_LCA(a, b);
    }
};

vector<int> bfs(vector<vector<int>>& graph) {
    queue<int> q;
    vector<int> depth(graph.size(), 0);
    q.push(1);
    while (!q.empty()) {
        auto node = q.front();
        q.pop();

        for (auto u : graph[node]) {
            depth[u] = depth[node] + 1;
            q.push(u);
        }
    }

    return depth;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector<int> par(n + 1, -1);
    for (int i = 2; i <= n; i++)
        cin >> par[i];

    vector<vector<int>> graph(n + 1);
    for (int i = 2; i <= n; i++) {
        graph[par[i]].push_back(i);
    }

    vector<int> depth = bfs(graph);

    LCA lca(par, depth);

    int a, b;
    while (q--) {
        cin >> a >> b;
        cout << lca.query(a, b) << "\n";
    }
}
