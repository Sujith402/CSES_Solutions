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

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> graph(n + 1);
    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        graph[a].push_back({b, -1});
    }

    vector<int> p(n + 1, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 1});
    vector<int> done(n + 1, 0), dist(n + 1);
    while (!pq.empty()) {
        int v = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        if (dist[v] < d) continue;

        for (auto x : graph[v]) {
            if (dist[v] + x.second < dist[x.first]) {
                dist[x.first] = dist[v] + x.second;
                pq.push({dist[x.first], x.first});
                p[x.first] = v;
            }
        }
    }

    if (p[n] == -1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    vector<int> out;
    for (int s = n; s != 1;) {
        out.push_back(s);
        s = p[s];
        if (s == -1) {
            break;
        }
    }
    out.push_back(1);
    reverse(out.begin(), out.end());

    cout << out.size() << "\n";
    for (auto x : out)
        cout << x << " ";
    cout << "\n";
}
