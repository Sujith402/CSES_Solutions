#include "bits/stdc++.h"
using namespace std;
#define int long long
//#define debug(x) cout << #x << " : " << x << " "

#ifdef local
#include "../debugger.h"
#else
#define debug(...) 42;
#endif
const int M = 125251;
const int MOD = 1e9 + 7;

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (int i = 0; i < n; i++)
        cin >> grid[i];

    vector<vector<int>> monster_moves(n, vector<int>(m, INT_MAX));
    pair<int, int> player;
    queue<pair<int, pair<int, int>>> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'A') {
                player.first = i;
                player.second = j;
            }
            if (grid[i][j] == 'M') {
                monster_moves[i][j] = 0;
                q.push({0, {i, j}});
                // num_monsters++;
            }
        }
    }

    vector<pair<int, int>> dir{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    vector<char> eng_dir{'R', 'L', 'D', 'U'};

    while (!q.empty()) {
        auto curr = q.front();
        q.pop();
        for (auto d : dir) {
            int x = curr.second.first + d.first;
            int y = curr.second.second + d.second;
            if (x < 0 || x >= n || y < 0 || y >= m)
                continue;
            if (grid[x][y] == '#')
                continue;
            if (monster_moves[x][y] > curr.first + 1) {
                monster_moves[x][y] = curr.first + 1;
                q.push({curr.first + 1, {x, y}});
            }
        }
    }

    vector<string> player_moves_eng(n, string(m, '.'));
    map<char, pair<int, int>> backtrack;
    backtrack['L'] = {0, 1};
    backtrack['R'] = {0, -1};
    backtrack['U'] = {1, 0};
    backtrack['D'] = {-1, 0};

    string out = "";

    vector<vector<bool>> visited(n, vector<bool>(m, 0));
    visited[player.first][player.second] = 1;
    q.push({0, {player.first, player.second}});
    while (!q.empty()) {
        auto curr = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int x = curr.second.first + dir[i].first;
            int y = curr.second.second + dir[i].second;
            if (x < 0 || x >= n || y < 0 || y >= m) {
                x = curr.second.first;
                y = curr.second.second;
                while (x != player.first || y != player.second) {
                    char c = player_moves_eng[x][y];
                    out += c;
                    x += backtrack[c].first;
                    y += backtrack[c].second;
                }
                break;
            }
            if (visited[x][y] || grid[x][y] == '#')
                continue;
            if (curr.first + 1 < monster_moves[x][y]) {
                q.push({curr.first + 1, {x, y}});
                player_moves_eng[x][y] = eng_dir[i];
                visited[x][y] = 1;
            }
        }
        if (out.size() > 0)
            break;
    }
    reverse(out.begin(), out.end());

    if (out.size() > 0) {
        cout << "YES\n";
        cout << out.size() << "\n";
        cout << out << "\n";
    } else {
        if (player.first == 0 || player.first == n - 1 || player.second == 0 || player.second == m - 1) {
            cout << "YES\n0\n";
        } else {
            cout << "NO\n";
        }
    }
}