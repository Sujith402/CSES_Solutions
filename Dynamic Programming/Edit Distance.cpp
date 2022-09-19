
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

    string s1, s2;
    cin >> s1 >> s2;

    vector<vector<int>> dp(s1.size() + 1, vector<int>(s2.size() + 1, INT_MAX));
    dp[0][0] = 0;

    for (int i = 0; i <= s1.size(); i++) {
        for (int j = 0; j <= s2.size(); j++) {
            if (i - 1 >= 0) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
            }
            if (j - 1 >= 0) {
                dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
            }
            if (i - 1 >= 0 && j - 1 >= 0) {
                dp[i][j] = min(
                    dp[i][j],
                    dp[i - 1][j - 1] + (s1[i - 1] != s2[j - 1]));
            }
        }
    }
    // cout << s1.size() << "\n";
    // cout << s2.size() << "\n";

    cout << dp[s1.size()][s2.size()] << "\n";
}