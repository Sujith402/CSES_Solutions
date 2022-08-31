
#include "bits/stdc++.h"
using namespace std;
#define ll long long 
//#define debug(x) cout << #x << " : " << x << " "

#ifdef local
#include "../debugger.h"
#else
#define debug(...) 42;
#endif

bool is_okay(int x, int y, int n, int m) {
    if (x >= 0 && x < n && y >= 0 && y < m)
        return 1;
    return 0;
}

const int MOD = 1e9+7;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t,n,m;
    cin >> n >> m;
    
    vector<string> v (n);
    for (int i=0; i<n; i++)
        cin >> v[i];
    
    vector<vector<bool>> marked (n, vector<bool> (m, 0));
    stack<pair<int,int>> s;
    int out = 0;
    pair<int,int> dir[4] = {{1, 0} , {-1, 0}, {0, 1}, {0,-1}};
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (v[i][j] == '.' && !marked[i][j]) {
                out++;
                s.push({i,j});
                pair<int,int> p;
                while (!s.empty()) {
                    p = s.top();
                    //cout << p  << "\n";
                    marked[p.first][p.second] = 1;
                    s.pop();
                    for (auto d: dir)
                        if (is_okay(p.first+d.first,p.second+d.second,n,m) && v[p.first+d.first][p.second+d.second]=='.' && !marked[p.first+d.first][p.second+d.second]){
                            s.push({p.first+d.first, p.second+d.second});                     
                        }
                }
                //debug(marked);
                //cout << "\n";
            }
        }
    }
    cout << out << "\n";
}