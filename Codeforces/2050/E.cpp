#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;

constexpr int inf = 1E9;

void solve() {
    std::string a, b, c;
    std::cin >> a >> b >> c;
    
    int n = a.size(), m = b.size();
    std::vector dp(n + 1, std::vector<int>(m + 1, inf));
    dp[0][0] = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i < n) {
                dp[i + 1][j] = std::min(dp[i + 1][j], dp[i][j] + (a[i] != c[i + j]));
            }
            if (j < m) {
                dp[i][j + 1] = std::min(dp[i][j + 1], dp[i][j] + (b[j] != c[i + j]));
            }
        }
    }
    
    std::cout << dp[n][m] << "\n";
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