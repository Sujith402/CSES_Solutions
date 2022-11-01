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
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];

    vector<int> present(M, 0);
    for (int i = 0; i < n; i++) {
        present[v[i]]++;
    }
    // Sieve of Eratosthenes - modified
    int ans = 1;
    for (int i = M - 1; i >= 2; i--) {
        int count = 0;
        for (int j = i; j < M; j += i) {
            if (present[j])
                count += present[j];
        }
        if (count > 1) {
            ans = i;
            break;
        }
    }

    cout << ans << "\n";
}
