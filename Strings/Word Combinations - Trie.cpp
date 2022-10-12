#include "bits/stdc++.h"
using namespace std;
#define int long long

#ifdef local
#include "../debugger.h"
#else
#define debug(...) 42;
#endif

const int MOD = 1e9 + 7;

struct node {
    node* c[26];
    bool valid;
};

struct Trie {
    node* head;

    Trie(vector<string>& words) {
        head = create_node();
        node* curr;
        for (auto& s : words) {
            curr = head;
            for (int j = 0; j < s.size(); j++) {
                if (curr->c[s[j] - 'a'] == nullptr) {
                    curr->c[s[j] - 'a'] = create_node();
                }
                curr = curr->c[s[j] - 'a'];
            }
            curr->valid = true;
        }
    }

    node* create_node() {
        node* n = new node;
        for (int i = 0; i < 26; i++) {
            n->c[i] = nullptr;
        }
        n->valid = false;
        return n;
    }

    void delete_node(node* n) {
        for (int i = 0; i < 26; i++) {
            if (n->c[i] != nullptr)
                delete_node(n->c[i]);
        }
        delete n;
    }

    ~Trie() {
        delete_node(head);
    }
};

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    string s;
    cin >> s;
    cin >> n;
    vector<string> words(n);
    for (int i = 0; i < n; i++) {
        cin >> words[i];
    }

    // dp[i] => number of ways to make substring [i...s.size()-1]
    vector<int> dp(s.size() + 1);
    dp[s.size()] = 1;

    Trie trie(words);

    for (int i = s.size() - 1; i >= 0; i--) {
        node* curr = trie.head;
        for (int j = i; j < s.size(); j++) {
            if (curr->c[s[j] - 'a'] == nullptr)
                break;
            curr = curr->c[s[j] - 'a'];
            if (curr->valid) {
                dp[i] = (dp[i] + dp[j + 1]) % MOD;
            }
        }
    }

    debug(dp);

    cout << dp[0] << "\n";
}
