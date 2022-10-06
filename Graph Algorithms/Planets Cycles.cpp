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

    int n;
    cin >> n;
    vector<int> next(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> next[i];

    vector<int> out(n + 1, 0);
    vector<bool> visited(n + 1, 0);
    vector<int> cycle_len(n + 1, 0);
    stack<int> s;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            s.push(i);
            visited[i] = true;
            while (!visited[next[s.top()]]) {
                visited[next[s.top()]] = true;
                s.push(next[s.top()]);
            }

            // 1st pass of a connected component
            if (out[next[s.top()]] == 0) {
                // 1st pass: Calculate cycle len
                // 2nd pass: Populate cycle len for nodes which are a part of the cycle
                int start = next[s.top()];
                int curr = next[start];
                int len = 1;
                while (curr != start) {
                    len++;
                    curr = next[curr];
                    // cerr << "HERE\n";
                }
                curr = s.top();
                if (curr == start) {
                    s.pop();
                    cycle_len[curr] = len;
                    out[curr] = len;
                } else {
                    while (curr != start) {
                        curr = s.top();
                        s.pop();
                        cycle_len[curr] = len;
                        out[curr] = len;
                    }
                }
                // cout << i << " " << len << "\n";
                while (!s.empty()) {
                    len++;
                    out[s.top()] = len;
                    s.pop();
                }
            }
            // All subsequent start nodes of a component who's cycle length
            // has already been calculated
            else {
                while (!s.empty()) {
                    out[s.top()] = out[next[s.top()]] + 1;
                    s.pop();
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << out[i] << " ";
    }
    cout << "\n";
}
