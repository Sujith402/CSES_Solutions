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

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> primes(k);
    for (int& x : primes) {
        cin >> x;
    }

    // index is odd, positive
    // else negative
    // follows from inclusion-exclusion
    vector<int> countByNumDivisors(k + 1, 0);

    // bitmask to generate all possible subsets of the primes
    for (int mask = 1; mask < (1 << k); mask++) {
        int temp = n;
        int num_div = 0;
        for (int i = 0; i < k; i++) {
            if ((1 << i) & mask) {
                // Remember this
                //  floor(n/(a*b*c...)) can be split up and done without loss of information
                //  why? No idea.
                temp /= primes[i];
                num_div++;
            }
        }
        countByNumDivisors[num_div] += temp;
    }

    int ans = 0;
    for (int i = 1; i <= k; i++) {
        if (i % 2) {
            ans += countByNumDivisors[i];
        } else {
            ans -= countByNumDivisors[i];
        }
    }

    cout << ans << "\n";
}
