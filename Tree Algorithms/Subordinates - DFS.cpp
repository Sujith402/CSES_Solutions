#include "bits/stdc++.h"
using namespace std;
#define int long long

#ifdef local
#include "../debugger.h"
#else
#define debug(...) 42;
#endif

const int M = 1e14;
const int MOD = 1e9 + 7;

// lg(10^7) < 25
const int k = 25;

vector<int> ans;

int dfs(int node, vector<vector<int>>& graph) {
    for (auto x : graph[node]) {
        ans[node] += (dfs(x, graph) + 1);
    }
    return ans[node];
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n;
    vector<vector<int>> graph(n + 1);

    int temp;
    for (int i = 2; i <= n; i++) {
        cin >> temp;
        graph[temp].push_back(i);
    }

    ans.assign(n + 1, 0);
    dfs(1, graph);

    for (int i = 1; i <= n; i++)
        cout << ans[i] << " ";
    cout << "\n";
}
