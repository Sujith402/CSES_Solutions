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

vector<int> shortest_path(int start, vector<vector<pair<int,int>>> graph) {
    vector<int> out (graph.size(), M);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0,start});
    pair<int,int> p;
    while(!pq.empty()) {
        while(!pq.empty() && out[pq.top().second] != M) {
            pq.pop();
        }
        if (pq.empty()) 
            break;
        
        p = pq.top();
        pq.pop();
        out[p.second] = p.first;
        for (auto node:graph[p.second]){
            pq.push({node.second + p.first, node.first});
        }
    }

    return out;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n,m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> graph (n+1), rev_graph(n+1);
    int a,b,w;
    for (int i=0; i<m; i++) {
        cin >> a >> b >> w;	
        graph[a].push_back({b,w});
        rev_graph[b].push_back({a,w});
    }

    auto from1 = shortest_path(1, graph);
    auto toN = shortest_path(n, rev_graph);

    int out = INT64_MAX;
    for (int i=1; i<=n; i++) {
        for (auto p: graph[i]) {
            if (from1[i] != M && toN[p.first] != M) {
                out = min(out, from1[i] + p.second/2 + toN[p.first]);
            }
        }
    }

    cout << out << "\n";

}
