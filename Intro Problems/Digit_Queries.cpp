#include "bits/stdc++.h"
using namespace std;
#define ll long long 
#define debug(x) cout << #x << " : " << x << " "

template<typename T1, typename T2> 
ostream& operator<<(ostream& os, pair<T1, T2> p) {
    os << p.first << " " << p.second;
    return os;
}

const int MOD = 1e9+7;

ll power(int base, int exp) {
    ll res = 1;
    for (int i=0; i<exp; i++) {
        res *= base;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int q;
    ll k;
    cin >> q;
    while (q--) {
        cin >> k;
        long long lim = 9;
        int dig = 1;
        if (k<=9) {
            cout << k << "\n";
            continue;
        }

        while (lim < k) {
            k -= lim;
            dig++;
            lim = 9*power(10,dig-1)*dig;
        }

        k--;
        ll num = power(10,dig - 1) + k/dig;
        string s = to_string(num);
        cout << s[k%dig] << "\n";

    }
}