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

    vector<int> pref_sum(n);
    pref_sum[0] = v[0];
    for (int i = 1; i < n; i++)
        pref_sum[i] = pref_sum[i - 1] + v[i];

    // dp[i][j] is max score that the first player can get
    // in list[i..j]
    // thinking of it as max difference can help eliminate
    // need for a prefix sum
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        dp[i][i] = v[i];
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            dp[i][j] = max(
                (pref_sum[j] - pref_sum[i] - dp[i + 1][j]) + v[i],
                (pref_sum[j - 1] - (i - 1 >= 0 ? pref_sum[i - 1] : 0) - dp[i][j - 1] + v[j]));
        }
    }

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    cout << dp[0][n - 1] << "\n";
}