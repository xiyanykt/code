#include<bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f64 = long double;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

#ifndef ONLINE_JUDGE
#include "algo/debug.hpp"
#else
#define debug(...) (void)42
#endif

template<class T>
constexpr bool chmax(T& x, T y) {
    if (y > x) {
        x = y;
        return true;
    }
    return false;
}

template<class T>
constexpr bool chmin(T& x, T y) {
    if (y < x) {
        x = y;
        return true;
    }
    return false;
}

constexpr int dx[] = {0, 0, 1, -1};
constexpr int dy[] = {1, -1, 0, 0};

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::string>s(n + 1);
    for (int i = 1; i <= n; i += 1) {
        std::cin >> s[i];
        s[i] = " " + s[i];
    }

    int res = 1E9;
    std::vector<std::vector<bool>>vis(n + 1, std::vector<bool>(m + 1));
    auto bfs = [&](int sx, int sy) {
        std::queue<std::pair<int, int>>q;
        q.push({sx, sy});
        vis[sx][sy] = true;
        std::vector<std::pair<int, int>>p;
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            p.push_back({x, y});
            for (int k = 0; k < 4; k += 1) {
                int nx = x + dx[k], ny = y + dy[k];
                if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && !vis[nx][ny] && s[nx][ny] == '1') {
                    q.push({nx, ny});
                    vis[nx][ny] = true;
                }
            }
        }
        std::set<std::pair<int, int>>del;
        for (const auto & [x, y] : p) {
            for (int k = 0; k < 4; k += 1) {
                int nx = x + dx[k], ny = y + dy[k];
                if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && s[nx][ny] == '0') {
                    del.insert({nx, ny});
                }
            }
        }
        chmin(res, int(del.size()));
    };

    for (int x = 1; x <= n; x += 1) {
        for (int y = 1; y <= m; y += 1) {
            if (s[x][y] == '1' && !vis[x][y]) {
                bfs(x, y);
            }
        }
    }

    std::cout << res << '\n';
    return 0;
}