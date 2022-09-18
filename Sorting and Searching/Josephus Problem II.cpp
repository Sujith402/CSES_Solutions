
#include "bits/stdc++.h"
using namespace std;
#define ll long long
//#define debug(x) cout << #x << " : " << x << " "

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

#ifdef local
#include "../debugger.h"
#else
#define debug(...) 42;
#endif
const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ordered_set os;
    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
        os.insert(i);
    }

    int start = 0;
    int curr;
    int lim = n;
    for (int i = 1; i <= lim; i++) {
        start = (start + k) % n;
        curr = *(os.find_by_order(start));
        cout << curr << " ";
        os.erase(curr);
        n--;
    }
    cout << "\n";
}