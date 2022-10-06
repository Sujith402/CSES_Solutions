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

class SegTree {
    vector<int> delta, hi, lo, Val;

    void init(int node, int l, int r) {
        lo[node] = l;
        hi[node] = r;

        if (l == r)
            return;
        int m = (l + r) / 2;
        init(2 * node, l, m);
        init(2 * node + 1, m + 1, r);
    }

    void prop(int node) {
        delta[2 * node] += delta[node];
        delta[2 * node + 1] += delta[node];
        delta[node] = 0;
    }

    void update(int node) {
        Val[node] = Val[2 * node] + delta[2 * node] + Val[2 * node + 1] + delta[2 * node + 1];
    }

    int val(int node, int l, int r) {
        if (r < lo[node] || l > hi[node])
            return 0;

        if (lo[node] >= l && hi[node] <= r)
            return Val[node] + delta[node];

        prop(node);

        int ValLeft = val(2 * node, l, r);
        int ValRight = val(2 * node + 1, l, r);

        // update(node);
        // cout << ValLeft << " " << ValRight << "\n";

        return ValLeft | ValRight;
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

        // update(node);
    }

   public:
    // why 4*n? ensure leaves have traversable children
    // check the 4*n thing
    SegTree(int n) {
        delta.assign(4 * n + 1, 0);
        hi.assign(4 * n + 1, 0);
        lo.assign(4 * n + 1, 0);
        Val.assign(4 * n + 1, 0);

        init(1, 1, n);
    }

    void increment(int l, int r, int val) {
        increment(1, l, r, val);
    }

    int val(int l, int r) {
        // debug(Val);
        // debug(delta);
        // cout << "\n";
        return val(1, l, r);
    }
};

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    read(v);

    SegTree st(n);
    for (int i = 0; i < n; i++) {
        st.increment(i + 1, i + 1, v[i]);
    }

    int l, r;
    int type, u;
    while (q--) {
        cin >> type;
        if (type == 1) {
            cin >> l >> r >> u;
            st.increment(l, r, u);
        } else {
            cin >> l;
            cout << st.val(l, l) << "\n";
        }
    }
}
