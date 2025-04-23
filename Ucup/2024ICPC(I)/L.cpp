#include <bits/stdc++.h>
using namespace std;

struct dsu {
    vector<int> fa, sz;
    dsu(int n) : fa(n), sz(n, 1) { iota(fa.begin(), fa.end(), 0); }

    int find(int x) {
        while (x != fa[x]) x = fa[x] = fa[fa[x]];
        return x;
    }
    bool same(int x, int y) { return find(x) == find(y); }
    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        sz[x] += sz[y], fa[y] = x;
        return true;
    }
    int size(int x) { return sz[find(x)]; }

    vector<vector<int>> groups() {
        vector<vector<int>> res(fa.size());
        for (int i = 0; i < fa.size(); i++) {
            res[find(i)].push_back(i);
        }
        res.erase(remove_if(res.begin(), res.end(),
            [&](const auto &v) { return v.empty(); }), res.end());
        return res;
    }
};

int read(int ch1, int ch2) {
    return 50 * (ch1 - 48) + ch2 - 48;
}

void solve() {
    int n, l, q;
    cin >> n >> l >> q;
    vector<vector<pair<int, int>>> adj(n);
    dsu d(n);
    for (int i = 0; i < l; i++) {
        string str;
        cin >> str;
        vector<int> perm(n);
        map<int, int> freq;
        for (int j = 0; j < n; j++) {
            perm[j] = read(str[2 * j], str[2 * j + 1]) - 1;
            freq[perm[j]]++;
        }
        if (freq.size() == n) {
            for (int j = 0; j < n; j++) {
                if (d.merge(j, perm[j])) {
                    adj[j].emplace_back(perm[j], i);
                    adj[perm[j]].emplace_back(j, i);
                }
            }
        } else if (freq.size() == n - 1) {
            int x;
            for (int j = 0; j < n; j++) {
                if (!freq.count(j)) {
                    x = j;
                    break;
                }
            }
            for (int j = 0; j < n; j++) {
                if (freq[perm[j]] > 1) {
                    adj[j].emplace_back(x, i);
                }
            }
        }
    }
    vector dist(n, vector<int>(n, l));
    for (int s = 0; s < n; s++) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
        q.emplace(dist[s][s] = -1, s);
        while (!q.empty()) {
            auto [d, x] = q.top();
            q.pop();
            if (d != dist[s][x]) continue;
            for (auto [y, w] : adj[x]) {
                int nd = max(d, w);
                if (nd < dist[s][y]) {
                    q.emplace(dist[s][y] = nd, y);
                }
            }
        }
    }
    while (q--) {
        string str;
        cin >> str;
        int a = read(str[0], str[1]) - 1;
        int b = read(str[2], str[3]) - 1;
        int c = read(str[4], str[5]) - 1;
        cout.put(dist[a][b] <= c ? '1' : '0');
    }
    cout.put('\n');
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}