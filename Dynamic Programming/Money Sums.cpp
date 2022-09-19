#include "bits/stdc++.h"
using namespace std;
#define int long long
//#define debug(x) cout << #x << " : " << x << " "

#ifdef local
#include "../debugger.h"
#else
#define debug(...) 42;
#endif
const int M = 1e5 + 1;

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];

    vector<int> dp(M, 0);
    for (int i = 0; i < n; i++) {
        if (dp[v[i]] == 0)
            dp[v[i]] = i + 1;
        for (int j = 1; j < M; j++) {
            if (dp[j] != 0 && dp[j] != i + 1) {
                if (dp[j + v[i]] == 0)
                    dp[j + v[i]] = i + 1;
            }
        }

        // for (int j = 1; j <= 14; j++) {
        //     cout << dp[j] << " ";
        // }
        // cout << "\n";
    }

    vector<int> out;
    for (int i = 1; i <= M; i++) {
        if (dp[i] != 0)
            out.push_back(i);
    }

    cout << out.size() << "\n";
    for (auto x : out) {
        cout << x << " ";
    }
    cout << "\n";
}