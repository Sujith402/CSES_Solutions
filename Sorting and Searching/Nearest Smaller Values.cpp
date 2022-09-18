
#include "bits/stdc++.h"
using namespace std;
#define int long long
//#define debug(x) cout << #x << " : " << x << " "

#ifdef local
#include "../debugger.h"
#else
#define debug(...) 42;
#endif
const int MOD = 1e9 + 7;

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];

    stack<int> s;
    vector<int> out(n);
    for (int i = 0; i < n; i++) {
        while (!s.empty() && v[s.top()] >= v[i]) {
            s.pop();
        }
        if (s.empty()) {
            out[i] = 0;
        } else {
            out[i] = s.top() + 1;
        }
        s.push(i);
    }

    for (auto x : out) {
        cout << x << " ";
    }
    cout << "\n";
}