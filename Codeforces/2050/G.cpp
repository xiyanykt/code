#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<std::vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    std::vector<int> dp(n);
    int ans = 1;
    auto dfs = [&](this auto &&self, int x, int p) -> void {
        int v = adj[x].size() - 2;
        dp[x] = v;
        ans = std::max(ans, v + 2);
        for (auto y : adj[x]){
            if (y == p) {
                continue;
            }
            self(y, x);
            ans = std::max(ans, dp[x] + dp[y] + 2);
            dp[x] = std::max(dp[x], v + dp[y]);
        }
    };
    dfs(0, -1);
    
    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}