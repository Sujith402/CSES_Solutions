#include "bits/stdc++.h"
using namespace std;
#define int long long

#ifdef local
#include "../debugger.h"
#else
#define debug(...) 42;
#endif

const int MOD = 1e9 + 7;
const int M = 1e6 + 1;
const int K = 25;

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;

    vector<int> ans(M, 1);
    // Sieve of Eratosthenes
    for (int i = 2; i < M; i++) {
        for (int j = i; j < M; j += i) {
            ans[j]++;
        }
    }

    int x;
    while (n--) {
        cin >> x;
        cout << ans[x] << "\n";
    }
}
