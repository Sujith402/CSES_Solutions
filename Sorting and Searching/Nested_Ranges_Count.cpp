#include "bits/stdc++.h"
using namespace std;
#define ll long long 
#define debug(x) cout << #x << " : " << x << " "

struct range {
    int l, r;
    int index;

    bool operator < (const range & other) {
        if (l == other.l) {
            return r > other.r;
        }
        return l < other.l;
    }
};

struct FenwickTree {
    vector<int> table;
    int n;
    // 1-based indexing 
    FenwickTree(int m) {
        this->n = m;
        table.assign(m+1, 0);
    }
    //dynamically update tree in O(lgn)
    void update(int i, int delta) {
        while (i<=n) {
            table[i] += delta;
            i += i&-i;
        }
    }
    //compute prefix sum of [1,i] 
    int sum(int i) {
        int out = 0;
        while(i>0) {
            out += table[i];
            i -= i&-i;
        }
        return out;
    }
    //compute sum value of range [l,r]
    //check whether l-1 or l
    int rangeSum(int l, int r) {
        return sum(r) - sum(l-1);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;

    vector<range> v (n);
    vector<int> contains (n, 0), contained (n, 0);
    set<int> s;
    for (int i=0; i<n; i++) {
        cin >> v[i].l >> v[i].r;
        v[i].index = i;
        s.insert(v[i].r);
    }
    sort(v.begin(), v.end());

    //converting increasing values to an index lesser than n
    map<int,int> mp;
    int cnt = 0;
    for (auto val: s)
        mp[val] = ++cnt;

    FenwickTree bit (cnt);
    for (int i=0; i<n; i++) {
        contained[v[i].index] = bit.rangeSum(mp[v[i].r], cnt); 
        bit.update(mp[v[i].r], 1);
    }

    bit = FenwickTree (cnt);
    for (int i=n-1; i>=0; i--) {
        contains[v[i].index] = bit.rangeSum(1, mp[v[i].r]);
        bit.update(mp[v[i].r], 1);
    }

    for (int i=0; i<n; i++)
        cout << contains[i] << " ";
    cout << "\n";

    for (int i=0; i<n; i++)
        cout << contained[i] << " ";
    cout << "\n";
}

