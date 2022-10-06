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

class SegTree {
    vector<int> delta;
    vector<int> hi;
    vector<int> lo;
    vector<int> Sum;

    void init(int node, int l, int r) {
        lo[node] = l;
        hi[node] = r;

        if (l == r)
            return;
        int m = (l + r) / 2;
        init(2 * node, l, m);
        init(2 * node + 1, m + 1, r);
    }

    int sum(int node, int l, int r) {
        if (r < lo[node] || l > hi[node])
            return 0;

        if (lo[node] >= l && hi[node] <= r)
            return Sum[node] + delta[node];

        prop(node);

        int Left = sum(2 * node, l, r);
        int Right = sum(2 * node + 1, l, r);

        update(node);

        return Left + Right;
    }

    void prop(int node) {
        delta[2 * node] += delta[node];
        delta[2 * node + 1] += delta[node];
        delta[node] = 0;
    }

    void update(int node) {
        Sum[node] = Sum[2 * node] + delta[2 * node] + Sum[2 * node + 1] + delta[2 * node + 1];
    }

    void increment(int node, int l, int r, int val) {
        if (r < lo[node] || l > hi[node])
            return;

        if (lo[node] >= l && hi[node] <= r) {
            delta[node] += val;
            return;
        }

        prop(node);

        increment(2 * node, l, r, val);
        increment(2 * node + 1, l, r, val);

        update(node);
    }

   public:
    SegTree(int n) {
        delta.assign(4 * n + 1, 0);
        hi.assign(4 * n + 1, 0);
        lo.assign(4 * n + 1, 0);
        Sum.assign(4 * n + 1, 0);

        init(1, 1, n);
    }

    void increment(int l, int r, int val) {
        return increment(1, l, r, val);
    }

    int sum(int l, int r) {
        return sum(1, l, r);
    }
};
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n;
    vector<int> v(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    SegTree st(n);
    for (int i = 1; i <= n; i++) {
        st.increment(i, i, 1);
    }
    vector<int> out(n);

    for (int i = 0; i < n; i++) {
        cin >> m;
        int lo = 1;
        int hi = n;
        int mid;
        // for (int j = 1; j <= n; j++) {
        //     cout << st.sum(1, j) << " ";
        // }
        // cout << "\n";
        while (lo != hi) {
            mid = (lo + hi) / 2;
            if (st.sum(1, mid) >= m) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        out[i] = v[lo - 1];
        st.increment(lo, lo, -1);
    }

    for (int i : out)
        cout << i << " ";
    cout << "\n";
}
