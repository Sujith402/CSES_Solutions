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

    int n;
    cin >> n;

    // dp[i][j] is no of ways to get sum j using the
    // first i integers
    vector<vector<int>> dp(n + 1, vector<int>(M, 0));
    // for (int i = 0; i <= n; i++) {
    //     dp[i][0] = 1;
    // }
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= M; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j - i >= 0) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j - i]) % MOD;
            }
        }
    }

    // for (int i = 0; i <= n; i++) {
    //     for (int j = 0; j <= 20; j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    int sum = (n * (n + 1)) / 2;
    if (sum % 2 == 0) {
        cout << dp[n - 1][sum / 2] << "\n";
    } else {
        cout << 0 << "\n";
    }
}