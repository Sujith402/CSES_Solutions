
#include "bits/stdc++.h"
using namespace std;
#define ll long long 
//#define debug(x) cout << #x << " : " << x << " "

#ifdef local
#include "../debugger.h"
#else
#define debug(...) 42;
#endif

//encoding information that is DP-able
// https://www.youtube.com/watch?v=MxhA0bY31wM&t=1094s

const int MOD = 1e9+7;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t,n;
    cin >> t;

    // dp[i][j] => tower of height i with the top block being the jth type of 2-block 
    vector<vector<int>> dp (1000001, vector<int> (9));
    
    for (int i=1; i<=8; i++) {
        dp[1][i] = 1;
    }
    
    // 1 -> 1, 3, 5, 6, 7
    // 2 -> 1, 3, 5, 6, 7
    // 3 -> 2, 4, 8
    // 4 -> 2, 4, 8
    // 5 -> 1, 3, 5, 6, 7
    // 6 -> 1, 3, 5, 6, 7
    // 7 -> 1, 3, 5, 6, 7
    // 8 -> 2, 4, 8

    ll curr = 0;
    for (int i=2; i<1000001; i++) {
        curr = 0;
        for (int j : {3, 4, 8}) {
            curr = (curr + dp[i-1][j])%MOD;
        }
        dp[i][2] = dp[i][4] = dp[i][8] = curr;
        
        curr = 0;
        for (int j : {1, 2, 5, 6, 7}) {
            curr = (curr + dp[i-1][j])%MOD;
        }
        dp[i][1] = dp[i][3] = dp[i][6] = dp[i][5] = dp[i][7] = curr;
    }
    
    //for (int i=1; i<= 6; i++) {
    //    for (int j=1; j<= 8; j++) {
    //        cout << dp[i][j] << " ";
    //    }
    //    cout << "\n";
    //}
    
    while (t--) {
        cin >> n;
        cout << ((ll)dp[n][3] + dp[n][4])%MOD << "\n";
    }
}