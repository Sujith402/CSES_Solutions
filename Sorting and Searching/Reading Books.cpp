
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
    sort(v.begin(), v.end());

    int sum1 = 0, sum2 = v[n - 1];
    for (int i = 0; i < n - 1; i++)
        sum1 += v[i];

    int ans;
    if (sum1 >= sum2) {
        ans = sum1 + sum2;
    } else {
        ans = sum1 + sum2 + (sum2 - sum1);
    }
    cout << ans << "\n";
}