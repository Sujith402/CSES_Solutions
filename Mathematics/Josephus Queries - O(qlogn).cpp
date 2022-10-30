#include "bits/stdc++.h"
using namespace std;
#define int long long

#ifdef local
#include "../debugger.h"
#else
#define debug(...) 42;
#endif

const int MOD = 1e9 + 7;
const int K = 25;

int josephus(int n, int k) {
    // if n=1, you always choose 1 regardless of k
    // recursive call takes care of shifts
    if (n == 1)
        return 1;

    // account for odds => n+1
    if (k > (n + 1) / 2) {
        int temp = josephus(n / 2, k - (n + 1) / 2);
        // if even, shift is slightly different
        if (n % 2 == 1)
            return 2 * temp + 1;
        return 2 * temp - 1;
    } else {
        // k can be chosen within this n
        // do not let it go to zero if 2*k==n
        if (2 * k > n)
            return (2 * k) % n;
        return 2 * k;
    }
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, k, q;
    cin >> q;

    while (q--) {
        cin >> n >> k;
        cout << josephus(n, k) << "\n";
    }
}
