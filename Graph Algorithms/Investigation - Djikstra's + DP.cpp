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

struct Ans {
    int min_price, min_flights, max_flights, num_routes;
};

struct Comparator {
    bool operator()(pair<int, Ans>& p1, pair<int, Ans>& p2) {
        return p1.second.min_price < p2.second.min_price;
    }
};

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> graph(n + 1), rev_graph(n + 1);
    int a, b, w;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> w;
        graph[a].push_back({b, w});
        rev_graph[b].push_back({a, w});
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    vector<Ans> out(n + 1);
    for (int i = 1; i <= n; i++) {
        out[i].min_price = out[i].min_flights = INT64_MAX;
        out[i].max_flights = 0;
        out[i].num_routes = 0;
    }

    out[1].num_routes = 1;
    out[1].min_flights = 0;
    out[1].min_price = 0;

    pq.push({0, 1});

    while (!pq.empty()) {
        int curr_ans = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (curr_ans == INT64_MAX || curr_ans > out[node].min_price) continue;

        // out[node].min_price = curr_ans;
        for (auto p : graph[node]) {
            int v = p.first;
            int c = p.second;

            if (out[v].min_price > curr_ans + c) {
                out[v].min_price = curr_ans + c;
                out[v].max_flights = out[node].max_flights + 1;
                out[v].min_flights = out[node].min_flights + 1;
                out[v].num_routes = out[node].num_routes;
                pq.push({curr_ans + c, v});
            } else if (out[node].min_price + c == out[v].min_price) {
                out[v].max_flights = max(out[v].max_flights, out[node].max_flights + 1);
                out[v].min_flights = min(out[v].min_flights, out[node].min_flights + 1);
                out[v].num_routes = (out[node].num_routes + out[v].num_routes) % MOD;
            }
        }
    }

    cout << out[n].min_price << " " << out[n].num_routes << " " << out[n].min_flights << " " << out[n].max_flights << "\n";
}
