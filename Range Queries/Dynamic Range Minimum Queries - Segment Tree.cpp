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
    // hold current increment that has not been propogated
    vector<int> delta;
    // hi[i] => highest node node i is in charge of
    vector<int> hi;
    // lo[i] => lowest node node i is in charge of
    vector<int> lo;
    // Min[i] => minimum value encountered in subtree rooted at node i
    vector<int> Min;

    // initialize the range a node is responsible for
    void init(int node, int l, int r) {
        lo[node] = l;
        hi[node] = r;

        if (l == r)
            return;
        int m = (l + r) / 2;
        init(2 * node, l, m);
        init(2 * node + 1, m + 1, r);
    }

    int minimum(int node, int l, int r) {
        // of the form
        // |-----| [------] or [------]  |-----|
        if (r < lo[node] || l > hi[node])
            return INT_MAX;

        // |----[-----]----|
        if (lo[node] >= l && hi[node] <= r)
            return Min[node] + delta[node];

        // All other forms i.e. separate calls have to be made
        // to left and right subtrees
        prop(node);

        int MinLeft = minimum(2 * node, l, r);
        int MinRight = minimum(2 * node + 1, l, r);

        update(node);

        return min(MinLeft, MinRight);
    }

    // lazily propogate delta
    void prop(int node) {
        delta[2 * node] += delta[node];
        delta[2 * node + 1] += delta[node];
        delta[node] = 0;
    }

    // after update is called, Minimum for a node is calculated
    void update(int node) {
        Min[node] = min(Min[2 * node] + delta[2 * node], Min[2 * node + 1] + delta[2 * node + 1]);
    }

    // similar to minimum
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
    // why 4*n? ensure leaves have traversable children
    // check the 4*n thing
    SegTree(int n) {
        delta.assign(4 * n + 1, 0);
        hi.assign(4 * n + 1, 0);
        lo.assign(4 * n + 1, 0);
        Min.assign(4 * n + 1, 0);

        init(1, 1, n);
    }

    void increment(int l, int r, int val) {
        return increment(1, l, r, val);
    }

    int minimum(int l, int r) {
        return minimum(1, l, r);
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
    // debug(st.lo);
    // debug(st.hi);
    // debug(st.Min);

    int type, l, r;
    while (q--) {
        cin >> type >> l >> r;
        if (type == 1) {
            st.increment(l, l, r - v[l - 1]);
            v[l - 1] = r;
        } else {
            cout << st.minimum(l, r) << "\n";
        }
    }
}
