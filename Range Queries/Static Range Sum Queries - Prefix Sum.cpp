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

void read(vector<int>& v) {
    for (int i = 0; i < v.size(); i++)
        cin >> v[i];
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    read(v);

    for (int i = 1; i < n; i++) {
        v[i] += v[i - 1];
    }

    int a, b;
    while (q--) {
        cin >> a >> b;
        a--, b--;
        cout << v[b] - (a - 1 >= 0 ? v[a - 1] : 0) << "\n";
    }
}
