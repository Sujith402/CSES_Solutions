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

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1);
    int x, y;
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    // for (int i = 1; i <= n; i++) {
    //     for (auto x : graph[i])
    //         cout << x << " ";
    //     cout << "\n";
    // }

    vector<int> back_ptr(n + 1, -1);
    vector<bool> found(n + 1, 0);
    int start = 1;
    stack<int> s;
    s.push(1);
    back_ptr[1] = 0;
    int curr;
    vector<int> out;
    while (!s.empty()) {
        curr = s.top();
        found[curr] = 1;
        // cout << curr << " ";
        // flush(cout);
        s.pop();
        for (auto node : graph[curr]) {
            if (!found[node]) {
                s.push(node);
                back_ptr[node] = curr;
            } else if (back_ptr[curr] == node) {
                continue;
            } else {
                out.push_back(node);
                while (curr != node) {
                    out.push_back(curr);
                    curr = back_ptr[curr];
                }
                out.push_back(node);
                break;
            }
        }
        if (out.size() != 0)
            break;
        if (s.empty()) {
            start++;
            for (int i = start; i <= n; i++) {
                if (!found[i]) {
                    start = i;
                    s.push(start);
                    back_ptr[start] = 0;
                    found[i] = 1;
                    break;
                }
            }
        }
        // for (int i = 1; i <= n; i++) {
        //     cout << back_ptr[i] << " ";
        // }
        // cout << endl;
    }
    // cout << "\n";
    if (out.size() == 0) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << out.size() << "\n";
        for (auto x : out) {
            cout << x << " ";
        }
        cout << "\n";
    }
}