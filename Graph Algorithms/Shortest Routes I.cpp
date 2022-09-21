#include "bits/stdc++.h"
using namespace std;
#define int long long
//#define debug(x) cout << #x << " : " << x << " "

#ifdef local
#include "../debugger.h"
#else
#define debug(...) 42;
#endif
const int M = 125251;
const int MOD = 1e9 + 7;

class Compare {
   public:
    bool operator()(pair<int, int> p1, pair<int, int> p2) {
        if (p1.second == p2.second)
            return p1.first > p2.first;
        return p1.second > p2.second;
    }
};

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> graph(n + 1);
    int x, y, w;
    for (int i = 0; i < m; i++) {
        cin >> x >> y >> w;
        graph[x].push_back({y, w});
    }

    // debug(graph);

    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;
    vector<int> out(n + 1, 0), visited(n + 1, 0);
    pq.push({1, 0});
    while (!pq.empty()) {
        while (!pq.empty() && visited[pq.top().first]) {
            pq.pop();
        }
        if (pq.empty()) {
            break;
        }
        auto curr = pq.top();
        visited[curr.first] = 1;
        out[curr.first] = curr.second;
        for (auto node : graph[curr.first]) {
            if (!visited[node.first]) {
                pq.push({node.first, curr.second + node.second});
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << out[i] << " ";
    }
    cout << "\n";
}