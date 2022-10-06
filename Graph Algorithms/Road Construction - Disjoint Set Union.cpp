#include "bits/stdc++.h"
using namespace std;
#define int long long
//#define debug(x) cout << #x << " : " << x << " "

#ifdef local
#include "../debugger.h"
#else
#define debug(...) 42;
#endif
const int M = 1e14;
const int MOD = 1e9 + 7;

struct Edge {
    int u, v, w;

    bool operator<(const Edge& e) {
        return this->w < e.w;
    }
};

class dsu {
   public:
    vector<int> p;
    vector<int> size;
    vector<int> group_size;
    int n;
    dsu(int _n) : n(_n) {
        p.resize(n);
        // fill (p.begin(),p.end(),-1);
        iota(p.begin(), p.end(), 0);
        size.resize(n, 1);
        group_size.resize(n, 1);
    }
    int parent(int x) {
        // path compression takes place here
        if (x == p[x])
            return x;
        else
            return p[x] = parent(p[x]);
    }
    inline bool unite(int x, int y) {
        x = parent(x);
        y = parent(y);
        if (x != y) {
            if (size[x] > size[y])
                swap(x, y);
            p[x] = y;
            size[x] += size[y];
            group_size[x] += group_size[y];
            group_size[y] = group_size[x];
            return true;
        }
        return false;
    }
};

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    int largest_comp_size = 1;
    int num_comp = n;
    dsu DSU(n);
    while (q--) {
        int u, v;
        cin >> u >> v;
        if (DSU.unite(u - 1, v - 1)) {
            num_comp--;
        }
        // debug(DSU.group_size);
        largest_comp_size = max({largest_comp_size, DSU.group_size[DSU.parent(u - 1)], DSU.group_size[DSU.parent(v - 1)]});

        cout << num_comp << " " << largest_comp_size << "\n";
    }
}
