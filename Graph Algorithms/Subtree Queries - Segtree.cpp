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

class SegTree {
    vector<int> delta;
    vector<int> hi;
    vector<int> lo;
    vector<int> Min;

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
            return Min[node] + delta[node];

        prop(node);

        int MinLeft = sum(2 * node, l, r);
        int MinRight = sum(2 * node + 1, l, r);

        update(node);

        return MinLeft + MinRight;
    }

    void prop(int node) {
        delta[2 * node] += delta[node];
        delta[2 * node + 1] += delta[node];
        delta[node] = 0;
    }

    void update(int node) {
        Min[node] = Min[2 * node] + delta[2 * node] + Min[2 * node + 1] + delta[2 * node + 1];
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
        Min.assign(4 * n + 1, 0);

        init(1, 1, n);
    }

    void increment(int l, int r, int val) {
        return increment(1, l, r, val);
    }

    int sum(int l, int r) {
        return sum(1, l, r);
    }
};

struct range {
    int start, end;
};

int m;
vector<range> mp;

void dfs(int curr, int p, vector<vector<int>>& graph) {
    mp[curr].start = m;
    for (int next : graph[curr]) {
        if (next != p) {
            dfs(next, curr, graph);
            m++;
        }
    }
    mp[curr].end = m;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> v[i];

    SegTree st(n + 1);

    vector<vector<int>> graph(n + 1);

    // mp[i].end -> node_val
    // subtree_sum[i] => sum of range(mp[i].start, mp[i].end - 1);
    mp.resize(n + 1);
    int x, y;
    for (int i = 1; i < n; i++) {
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    m = 1;
    dfs(1, -1, graph);

    for (int i = 1; i <= n; i++) {
        st.increment(mp[i].end, mp[i].end, v[i]);
    }

    // for (int i = 1; i <= n; i++)
    //     cout << mp[i].start << " " << mp[i].end << "\n";
    // cout << "\n";

    int choice;
    while (q--) {
        cin >> choice;
        if (choice == 2) {
            cin >> x;
            cout << st.sum(mp[x].start, mp[x].end) << "\n";
        } else {
            cin >> x >> y;
            st.increment(mp[x].end, mp[x].end, y - st.sum(mp[x].end, mp[x].end));
        }
    }
}
