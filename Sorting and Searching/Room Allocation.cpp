
#include "bits/stdc++.h"
using namespace std;
#define ll long long
//#define debug(x) cout << #x << " : " << x << " "

#ifdef local
#include "../debugger.h"
#else
#define debug(...) 42;
#endif
const int MOD = 1e9 + 7;

struct room {
    int start, end;

    bool operator<(const room& r1) {
        if (this->start == r1.start)
            return this->end < r1.end;
        return this->start < r1.start;
    }

    bool operator==(const room& r1) {
        return (start == r1.start) && (end == r1.end);
    }
};

bool cmp(pair<room, int> p1, pair<room, int> p2) {
    if (p1.first == p2.first)
        return p1.second < p2.second;
    return p1.first < p2.first;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<pair<room, int>> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].first.start >> v[i].first.end;
        v[i].second = i;
    }
    sort(v.begin(), v.end(), cmp);

    // for (int i = 0; i < n; i++) {
    //     cout << v[i].first.start << " " << v[i].first.end << " " << v[i].second << "\n";
    // }

    queue<int> available_rooms;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    int max_room = 1;

    vector<int> out(n);

    for (int i = 0; i < n; i++) {
        while (!pq.empty()) {
            auto p = pq.top();
            if (p.first < v[i].first.start) {
                available_rooms.push(p.second);
                pq.pop();
            } else {
                break;
            }
        }

        int curr_room;
        if (available_rooms.empty()) {
            curr_room = max_room;
            max_room++;
        } else {
            curr_room = available_rooms.front();
            available_rooms.pop();
        }
        pq.push({v[i].first.end, curr_room});
        out[v[i].second] = curr_room;
    }

    cout << max_room - 1 << "\n";
    for (auto x : out) {
        cout << x << " ";
    }
    cout << "\n";
}