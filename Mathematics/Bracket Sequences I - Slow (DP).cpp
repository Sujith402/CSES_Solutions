#include "bits/stdc++.h"
using namespace std;
#define int long long

#ifdef local
#include "../debugger.h"
#else
#define debug(...) 42;
#endif

const int MOD = 1e9 + 7;
const int M = 2e6 + 1;
const int K = 25;

// Slow -> 1e6 bound
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    if (n % 2 != 0) {
        cout << 0 << "\n";
        return 0;
    }
    n /= 2;
    // dp[i][j] is no_of_sequences possible if you have i open & j close brackets left
    vector<vector<int>> dp(n + 1, vector<int>(n + 1));

    for (int j = 1; j <= n; j++) {
        dp[0][j] = 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % MOD;
        }
    }

    cout << dp[n][n] << "\n";
}
