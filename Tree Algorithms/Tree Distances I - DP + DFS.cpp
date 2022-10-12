#include "bits/stdc++.h"
using namespace std;
#define int long long

#ifdef local
#include "../debugger.h"
#else
#define debug(...) 42;
#endif

const int MOD = 1e9 + 7;

void dfs(int curr, int p, vector<vector<int>>& graph, vector<int>& height, vector<int>& dist) {
    int m1 = -1;
    int m2 = -1;

    // calculate max_path_lengths 1 and 2 from curr node to one of it's subtree's leaves
    for (auto v : graph[curr]) {
        if (v != p) {
            if (height[v] >= m1) {
                m2 = m1;
                m1 = height[v];
            } else if (height[v] > m2)
                m2 = height[v];
        }
    }

    // check if parent's longest path has the current node
    for (auto v : graph[curr]) {
        if (v != p) {
            // checking if current path is on longest path of node v
            // if height[v] + 1 == m1 => use m2
            int s = ((height[v] == m1) ? m2 : m1);
            if (s == -1)
                dist[v] = 1 + dist[curr];
            else
                dist[v] = 1 + max(s + 1, dist[curr]);

            dfs(v, curr, graph, height, dist);
        }
    }
}

// calculate max depth of subtree of a particular node
void dfs1(int curr, int p, vector<vector<int>>& graph, vector<int>& height) {
    for (int u : graph[curr]) {
        if (u != p) {
            dfs1(u, curr, graph, height);
            height[curr] = max(height[u] + 1, height[curr]);
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

    // let's root it at 1
    // run a bfs in reverse to calculate height of nodes
    vector<int> height(n + 1, -1);
    vector<bool> done(n + 1, 0);
    queue<pair<int, int>> q;
    for (int i = 2; i <= n; i++) {
        if (graph[i].size() == 1) {
            q.push({0, i});
            height[i] = 0;
        }
    }

    dfs1(1, 0, graph, height);

    // while (!q.empty()) {
    //     int curr = q.front().second, p = q.front().first;
    //     cout << curr << " " << p << "\n";
    //     q.pop();

    //     // terminate at root
    //     if (curr == 1) continue;

    //     done[curr] = true;
    //     for (auto v : graph[curr]) {
    //         if (!done[v]) {
    //             q.push({curr, v});
    //         }
    //         if (v != p)
    //             height[v] = max(height[v], height[curr] + 1);
    //     }
    // }

    vector<int> out(n + 1);

    dfs(1, 0, graph, height, out);

    debug(out);
    debug(height);

    for (int i = 1; i <= n; i++) {
        cout << max(height[i], out[i]) << " ";
    }
    cout << "\n";
}
