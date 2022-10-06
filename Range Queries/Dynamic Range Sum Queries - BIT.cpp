#include "bits/stdc++.h"
using namespace std;
#define int long long

#ifdef local
#include "../debugger.h"
#else
#define debug(...) 42;
#endif

const int M = 1e14;
const int MOD = 1e9 + 7;

// lg(10^7) < 25
const int k = 25;

void read(vector<int>& v) {
    for (int i = 0; i < v.size(); i++)
        cin >> v[i];
}

struct FenwickTree {
    vector<int> table;
    int n;
    // 1-based indexing
    FenwickTree(int m) {
        this->n = m;
        table.assign(m + 1, 0);
    }
    // dynamically update tree in O(lgn)
    void update(int i, int delta) {
        while (i <= n) {
            table[i] += delta;
            i += i & -i;
        }
    }
    // compute prefix sum of [1,i]
    int sum(int i) {
        int out = 0;
        while (i > 0) {
            out += table[i];
            i -= i & -i;
        }
        return out;
    }
    // compute sum value of range [l,r]
    // check whether l-1 or l
    int rangeSum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    read(v);

    FenwickTree BIT(n);
    for (int i = 0; i < n; i++) {
        BIT.update(i + 1, v[i]);
    }

    int l, r;
    int type;
    while (q--) {
        cin >> type >> l >> r;
        if (type == 1) {
            BIT.update(l, r - v[l - 1]);
            v[l - 1] = r;
        } else {
            cout << BIT.rangeSum(l, r) << "\n";
        }
    }
}
