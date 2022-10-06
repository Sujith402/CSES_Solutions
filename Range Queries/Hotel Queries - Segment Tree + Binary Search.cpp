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
    vector<int> delta, hi, lo;
    vector<pair<int, int>> Max;

    void init(int node, int l, int r) {
        lo[node] = l;
        hi[node] = r;

        if (l == r) {
            Max[node].second = r;
            return;
        }
        int m = (l + r) / 2;
        init(2 * node, l, m);
        init(2 * node + 1, m + 1, r);
    }

    pair<int, int> maximum(int node, int l, int r) {
        if (r < lo[node] || l > hi[node])
            return {-1, -1};

        if (lo[node] >= l && hi[node] <= r)
            return {Max[node].first + delta[node], Max[node].second};

        prop(node);

        auto MaxLeft = maximum(2 * node, l, r);
        auto MaxRight = maximum(2 * node + 1, l, r);

        update(node);

        if (MaxLeft.first >= MaxRight.first)
            return MaxLeft;
        return MaxRight;
    }

    void prop(int node) {
        delta[2 * node] += delta[node];
        delta[2 * node + 1] += delta[node];
        delta[node] = 0;
    }

    void update(int node) {
        if (Max[2 * node].first + delta[2 * node] >= Max[2 * node + 1].first + delta[2 * node + 1])
            Max[node] = {Max[2 * node].first + delta[2 * node], Max[2 * node].second};
        else
            Max[node] = {Max[2 * node + 1].first + delta[2 * node + 1], Max[2 * node + 1].second};
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
        Max.assign(4 * n + 1, {0, 0});

        init(1, 1, n);
    }

    void increment(int l, int r, int val) {
        return increment(1, l, r, val);
    }

    pair<int, int> maximum(int l, int r) {
        return maximum(1, l, r);
    }

    void log() {
        debug(delta);
        debug(Max);
        debug(hi);
        debug(lo);
    }
};

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> v(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    SegTree st(n);
    for (int i = 0; i < n; i++) {
        st.increment(i + 1, i + 1, v[i]);
    }

    // st.log();

    vector<int> out(m);
    int g;
    for (int i = 0; i < m; i++) {
        cin >> g;
        int hi = n;
        int lo = 1;
        pair<int, int> res;
        while (lo != hi) {
            // cerr << lo << " " << hi << "\n";
            int mid = (lo + hi) / 2;
            res = st.maximum(1, mid);
            if (res.first >= g) {
                hi = mid;
                continue;
            }
            res = st.maximum(mid + 1, hi);
            if (res.first >= g) {
                lo = mid + 1;
            } else {
                lo = hi = 1;
            }
        }
        if (v[lo - 1] >= g) {
            out[i] = lo;
            v[lo - 1] -= g;
            st.increment(lo, lo, -g);
        } else {
            out[i] = 0;
        }
    }

    for (int i : out)
        cout << i << " ";
    cout << "\n";
}
