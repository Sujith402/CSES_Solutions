#include "bits/stdc++.h"
using namespace std;
#define ll long long 
#define debug(x) cout << #x << " : " << x << " "

template<typename T1, typename T2> 
ostream& operator<<(ostream& os, pair<T1, T2> p) {
    os << p.first << " " << p.second;
    return os;
}
const int MOD = 1e9+7;

#define DOWN 0
#define UP 1
#define LEFT 2
#define RIGHT 3
vector<pair<int,int>> dir = {{1,0}, {-1, 0}, {0,-1}, {0,1}};
vector<pair<int,int>> diag_dir = {{1,1}, {1,-1}, {-1,1}, {-1,-1}};
//vector<string> directions = {"D", "U", "L", "R"};
vector<vector<int>> board (7, vector<int> (7, 0));
string s;

bool is_valid(int row, int col){
    if (row>=0 && row<7 && col>=0 && col<7)
        return true;
    return false;
}

int count_paths(int row, int col, int move){
    if (row == 6 && col == 0) {
        if (move == 48){
            //cout << path << "\n";
            return 1;
        }
        return 0;
    }
    if (move == 48)
        return 0;

    vector<int> visited(4,-1);
    for (int i=0; i<4; i++) {
        if (is_valid(row+dir[i].first, col+dir[i].second)){
            visited[i] = board[row+dir[i].first][col+dir[i].second];
        }
    }

    if (!visited[RIGHT] && !visited[LEFT] && visited[UP] && visited[DOWN])
        return 0;
    if (!visited[UP] && !visited[DOWN] && visited[RIGHT] && visited[LEFT])
        return 0;

    for (int i=0; i<diag_dir.size(); i++) {
        auto d = diag_dir[i];
        int x, y;
        x = d.first == 1 ? DOWN : UP;
        y = d.second == 1 ? RIGHT : LEFT;
        if (is_valid(row+d.first,col+d.second) && board[row+d.first][col+d.second] == 1)
            if (!visited[x] && !visited[y]) 
                return 0;
    }

    int cnt = 0;
    if (s[move] == '?') {
        for (int i=0; i<dir.size(); i++) {
            auto d = dir[i];
            if (is_valid(row+d.first, col+d.second) && board[row+d.first][col+d.second] == 0){
                board[row+d.first][col+d.second] = 1;
                cnt += count_paths(row+d.first, col+d.second, move+1);
                board[row+d.first][col+d.second] = 0;
            }
        }
    } 
    else {
        pair<int,int> d;
        switch(s[move]) {
            case 'L':   d=dir[LEFT];
                        break;
            case 'R':   d=dir[RIGHT];
                        break;
            case 'U':   d=dir[UP];
                        break;
            case 'D':   d=dir[DOWN];
                        break;
        }
        if (is_valid(row+d.first, col+d.second) && board[row+d.first][col+d.second] == 0){
            board[row+d.first][col+d.second] = 1;
            cnt += count_paths(row+d.first, col+d.second, move+1 );
            board[row+d.first][col+d.second] = 0;
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> s;
    board[0][0] = 1;
    cout << count_paths(0,0,0) << "\n";
}