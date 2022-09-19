
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

    int a, b;
    cin >> a >> b;

    vector<vector<int>> dp(a + 1, vector<int>(b + 1, INT_MAX));
    for (int i = 1; i <= a; i++) {
        dp[i][1] = i - 1;
    }
    for (int j = 1; j <= b; j++) {
        dp[1][j] = j - 1;
    }

    for (int i = 2; i <= a; i++) {
        for (int j = 2; j <= b; j++) {
            if (i == j) {
                dp[i][j] = 0;
            }
            for (int k = 1; k < i; k++) {
                dp[i][j] = min(
                    dp[i][j],
                    dp[k][j] + dp[i - k][j] + 1);
            }
            for (int k = 1; k < j; k++) {
                dp[i][j] = min(
                    dp[i][j],
                    dp[i][j - k] + dp[i][k] + 1);
            }
        }
    }

    // for (int i = 1; i <= a; i++) {
    //     for (int j = 1; j <= b; j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    cout << dp[a][b] << "\n";
}