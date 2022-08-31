#include "bits/stdc++.h"
using namespace std;
#define ll long long 
#define debug(x) cout << #x << " : " << x << " "

const int MOD = 1e9+7;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,x;
	cin >> x;

    vector<int> dp (x+1, 0);

	for (int i=1; i<=9; i++) {
		dp[i] = 1;
	}

	for (int i=10; i<=x; i++) {
		vector<int> dig;
		int temp = i;
		while (temp > 0) {
			dig.push_back(temp%10);
			temp /= 10;
		}
		for (auto d: dig) {
			if (i-dig > 0)
				dp[i] = min(dp[i], dp[i-dig]+1);
		}
	}

	cout << dp[x] << "\n";

}