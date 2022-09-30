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
    int v, u, w;
};

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> graph(n + 1);
    int a, b, w;
    vector<edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    // d is initialized with 0 due to
    // 1. Shortest path is not required. The only thing that matters is if it becomes negative
    // 2. To account for disconnected components
    vector<int> d(n + 1);
    vector<int> p(n + 1, -1);

    int x = -1;
    for (int i = 0; i < n; i++) {
        x = -1;
        for (auto e : edges) {
            if (d[e.v] > d[e.u] + e.w) {
                d[e.v] = d[e.u] + e.w;
                p[e.v] = e.u;
                x = e.v;
            }
        }
    }
    // debug(p);

    if (x == -1) {
        cout << "NO\n";
    } else {
        // make sure the vertex ends up in the cycle
        //  as path length of any node back to cycle can be at most n-1
        //  get it's parent at the (n-1)th level which is guaranteed to
        //  be a part of the neg cycle
        for (int i = 0; i < n; i++) {
            x = p[x];
        }

        // next find the cycle
        vector<int> cycle;
        for (int v = x;; v = p[v]) {
            cycle.push_back(v);
            if (v == x && cycle.size() != 1) {
                break;
            }
        }

        // reverse to get correct order
        reverse(cycle.begin(), cycle.end());

        cout << "YES\n";
        for (auto node : cycle) {
            cout << node << " ";
        }
        cout << "\n";
    }
}
