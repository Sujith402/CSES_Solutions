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

    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pair<int, int>>> graph(n + 1);
    int a, b, w;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> w;
        graph[a].push_back({b, w});
    }

    // dist[u][k] => (k+1)th shortest distance to reach u
    vector<vector<int>> dist(n + 1, vector<int>(k, INT64_MAX));

    // min_heap => {cost, node}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 1});
    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (dist[u][k - 1] < d) continue;

        // sort can be avoided if dist is turned into an array of max heaps
        // since k<=10, 2D array also works

        for (auto e : graph[u]) {
            int c = e.second;
            int v = e.first;
            if (dist[v][k - 1] > d + c) {
                dist[v][k - 1] = c + d;
                pq.push({d + c, v});
                sort(dist[v].begin(), dist[v].end());
            }
        }
    }

    for (auto x : dist[n]) {
        cout << x << " ";
    }
    cout << "\n";
}
