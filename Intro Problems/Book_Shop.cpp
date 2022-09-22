
//column-major vs row-major access causes cache issues
//row-major is _always_ better
//column-major is shown to take up to 3x as much cycles due to cache miss


#include "bits/stdc++.h"
using namespace std;
#define ll long long 
//#define debug(x) cout << #x << " : " << x << " "

#ifdef local
#include "../debugger.h"
#else
#define debug(...) 42;
#endif

const int MOD = 1e9+7;

//struct book{
//    int price;
//    int pages;
//    
//};


//void solve(vector<book> books, int i, int j) {
//    if (i - books[j].price >= 0) {
//        if (dp[i - books[j].price][j-1] == -1) {
//            solve(books, i-books[j].price, j-1);
//        }
//        dp[i][j] = max( dp[i-books[j].price][j-1] + books[j].pages, dp[i][j-1]);
//    }
//    else 
//        dp[i][j] = dp[i][j-1];
//}

//void solve(vector<book> books, int x, int n) {
//    stack<pair<int,int>> s;
//    s.push({x, n});
//    pair<int,int> p;
//    while (!s.empty()) {
//        p = s.top();
//        if (dp[p.first][p.second - 1] == -1)
//            s.push({p.first, p.second-1});
//        if (p.first - books[p.second].price >= 0){
//            if (dp[p.first - books[p.second].price][p.second-1] == -1)
//                s.push({p.first - books[p.second].price , p.second-1});
//            if (dp[p.first - books[p.second].price][p.second-1] != -1 && dp[p.first][p.second - 1] != -1) {
//                dp[p.first][p.second] = max(dp[p.first][p.second - 1] , dp[p.first - books[p.second].price][p.second-1] + books[p.second].pages);
//                s.pop();
//            }
//        }
//        else {
//            if (dp[p.first][p.second - 1] != -1) {
//                dp[p.first][p.second] = dp[p.first][p.second - 1];
//                s.pop();
//            }
//        }
//    }    
//}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, x;
	cin >> n >> x;
    
    //vector<book> books (n+1);
    vector<int> price (n+1), pages (n+1);

    for (int i=1; i<=n; i++) 
        cin >> price[i];
    for (int i=1; i<=n; i++) 
        cin >> pages[i];
   
    vector<vector<int>> dp (n+1, vector<int> (x+1, 0));
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=x; j++) {
            //pick or don't pick
            dp[i][j] = dp[i-1][j];
            int other = j-price[i];
            if (other >= 0)
                dp[i][j] = max( dp[i-1][other] + pages[i], dp[i][j]);
        }
    }
   
    //debug(dp);
    //for (int i=0; i<=x; i++) {
    //    for (int j=0; j<n; j++)
    //        cout << dp[i][j] << " ";
    //    cout << "\n";
    //}

    cout << dp[n][x] << "\n";

}

