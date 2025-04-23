#include<bits/stdc++.h>

using i64 = long long;

template<class T>
struct Fenwick {
    int n;
    std::vector<T>a;
    Fenwick() = default;
    Fenwick(int n): n{n}, a(n + 1, T()) {}

    void add(int p, const T& v) {
        for (int i = p; i >= 1 && i <= n; i += i & -i) {
            a[i] += v;
        }
    }

    T sum(int p) {
        T res {};
        for (int i = p; i >= 1; i -= i & -i) {
            res += a[i];
        }
        return sum;
    }

    T range(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};

const int N = 1E6;
int16_t r[3][2 * N + 13];

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;

    std::vector<int>v[3];
    // std::unordered_map<int, int>r[3];
    for (int i = 1; i <= n; i += 1) {
        int x, y;
        std::cin >> x >> y;
        v[y].push_back(x);
        r[y][x + N] = 1;
    }

    for (int y = 0; y <= 2; y += 1) {
        std::sort(v[y].begin(), v[y].end());
    }

    std::vector<std::array<int, 6>>ans;
    for (int i = 0; i < v[1].size(); i += 1) {
        if (v[0].size() <= v[2].size()) {
            for (int j = 0; j < v[0].size(); j += 1) {
                int d = v[1][i] - v[0][j];
                if (r[2][v[1][i] + d + N]) {
                    ans.push_back({v[0][j], 0, v[1][i], 1, v[1][i] + d, 2});
                }
            }
        } else {
            for (int j = 0; j < v[2].size(); j += 1) {
                int d = v[1][i] - v[2][j];
                if (r[0][v[1][i] + d + N]) {
                    ans.push_back({v[1][i] + d, 0, v[1][i], 1, v[2][j], 2});
                }
            }
        }
    }

    if (ans.empty()) {
        std::cout << -1;
        return 0;
    }

    std::sort(ans.begin(), ans.end(), [&](const auto& v1, const auto& v2) {
        if (v1[2] == v2[2]) {
            return v1[0] < v2[0];
        }
        return v1[2] < v2[2];
    });
    ans.erase(std::unique(ans.begin(), ans.end()), ans.end());

    for (const auto &v : ans) {
        int x1 = v[0];
        int y1 = v[1];
        int x2 = v[2];
        int y2 = v[3];
        int x3 = v[4];
        int y3 = v[5];
        std::cout << '[' << x1 << ", " << y1 << "] [" << x2 << ", " << y2 << "] [" << x3 << ", " << y3 << "]\n";
    }
    return 0;
}
