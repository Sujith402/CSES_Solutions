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
    int n;
    dsu(int _n) : n(_n) {
        p.resize(n);
        // fill (p.begin(),p.end(),-1);
        iota(p.begin(), p.end(), 0);
        size.resize(n, 1);
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
            return true;
        }
        return false;
    }
};

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    sort(edges.begin(), edges.end());

    // for (auto e : edges) {
    //     cout << e.u << " " << e.v << " " << e.w << "\n";
    // }

    dsu DSU(n + 1);
    int out = 0;
    for (int i = 0; i < m; i++) {
        if (DSU.parent(edges[i].u) != DSU.parent(edges[i].v)) {
            DSU.unite(edges[i].u, edges[i].v);
            out += edges[i].w;
        }
    }
    bool poss = true;
    for (int i = 2; i <= n; i++) {
        if (DSU.parent(i) != DSU.parent(1)) {
            poss = false;
            break;
        }
    }

    if (poss) {
        cout << out << "\n";
    } else {
        cout << "IMPOSSIBLE\n";
    }
}
