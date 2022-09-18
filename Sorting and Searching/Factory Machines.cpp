
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

    int n, t;
    cin >> n >> t;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];

    int lo = 1, hi = 1e18, mid;
    int ans;
    mid = (hi + lo) / 2;
    while (lo < hi) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += (mid / v[i]);
            if (sum >= t)
                break;
        }
        if (sum >= t) {
            hi = mid;
            // ans = mid;
        } else {
            lo = mid + 1;
        }
        mid = (lo + hi) / 2;
    }

    cout << lo << "\n";
}