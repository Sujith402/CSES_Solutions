#include "bits/stdc++.h"
using namespace std;
#define int long long

#ifdef local
#include "../debugger.h"
#else
#define debug(...) 42;
#endif

const int MOD = 1e9 + 7;
const int K = 25;

vector<int> z_function(string& s) {
    int n = (int)s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;
    int n = (int)s.size();

    vector<int> z = z_function(s);
    vector<int> out;
    for (int i = 1; i < n; i++) {
        if (i + z[i] == n)
            out.push_back(i);
    }
    out.push_back(n);

    for (int x : out)
        cout << x << " ";
    cout << "\n";
}
