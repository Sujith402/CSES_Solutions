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

int binpow(int a, int b, int m) {
    int res = 1;
    while (b > 0) {
        if (b & 1) {
            res = (res * a) % m;
        }
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, a, b, c;
    cin >> n;

    while (n--) {
        cin >> a >> b >> c;
        // Fermat's Little Theorem states a^(p-1) === 1 (mod p) provided p is prime and p does not divide a
        //  b^c = q.(p-1) + r
        //  a^( b^c ) = a^( q.(p-1)+r )
        //  a^( b^c ) === (1^q).(a^r) (mod p)
        //  where r is (b^c) % (p-1)
        cout << binpow(a, binpow(b, c, MOD - 1), MOD) << "\n";
    }
}
