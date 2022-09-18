
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

    int n, x;
    cin >> n >> x;
    vector<int> v(n), ind(n);
    iota(ind.begin(), ind.end(), 1);
    for (int i = 0; i < n; i++)
        cin >> v[i];
    sort(ind.begin(), ind.end(),
         [&](int A, int B) -> bool {
             return v[A - 1] < v[B - 1];
         });

    // cout << v[2786] + v[464] + v[2265] << "\n";
    sort(v.begin(), v.end());

    // int lo = 0, hi = n - 1;
    bool done = false;

    for (int i = 0; i < n; i++) {
        int target = x - v[i];
        int lo = 0, hi = n - 1;
        while (lo < hi) {
            if (lo == i)
                lo++;
            if (hi == i)
                hi--;
            if (lo >= hi)
                break;

            if (v[lo] + v[hi] == target) {
                cout << ind[lo] << " " << ind[i] << " " << ind[hi] << "\n";
                done = true;
                break;
            } else if (v[lo] + v[hi] > target)
                hi--;
            else
                lo++;
        }
        if (done)
            break;
    }

    // while (lo < hi) {
    //     while (lo < hi && v[lo] + v[hi] >= x) {
    //         hi--;
    //     }
    //     int curr_lo = lo;
    //     cout << lo << " " << hi << "\n";
    //     while (curr_lo < hi) {
    //         int target = v[curr_lo] + v[hi];
    //         int mid = lower_bound(v.begin() + curr_lo + 1, v.begin() + hi, x - target) - v.begin();
    //         if (lo == 464 && hi == 2786) {
    //             cout << mid << "\n";
    //         }
    //         if (mid != hi) {
    //             if (target + v[mid] == x) {
    //                 cout << ind[curr_lo] << " " << ind[mid] << " " << ind[hi] << "\n";
    //                 done = true;
    //                 break;
    //             }
    //         }
    //         curr_lo++;
    //         if (v[curr_lo] + v[hi] >= x)
    //             break;
    //     }
    //     lo++;
    //     if (done)
    //         break;
    // }

    if (!done) {
        cout << "IMPOSSIBLE\n";
    }
}