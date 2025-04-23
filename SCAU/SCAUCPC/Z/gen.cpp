#include<bits/stdc++.h>
using i64 = long long;

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template <class T>
T rand(T l, T r) {
    return std::uniform_int_distribution<T>(l, r)(rng);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // ans = 0
    // constexpr int Kn = 877;

    // std::cout << Kn << '\n';

    // int x = rand(1, Kn);
    // for (int i = 1; i <= Kn; i += 1) {
    //     std::cout << x << " \n"[i == Kn];
    // }

    // rand ans
    constexpr int Kn = 887;

    int n = rand(0, 1) + Kn;
    int t = rand(1, n / 2);

    std::cout << n << '\n';
    for (int i = 1; i <= t; i += 1) {
        int x = rand(1, n), y = rand(1, n);
        while (x == y) {
            x = rand(1, n);
            y = rand(1, n);
        }
        std::cout << x << ' ' << y << ' ';
    }

    int d = n - 2 * t;
    if (d % 2 == 0) {
        int x = rand(1, n);
        for (int i = 1; i <= d / 2; i += 1) {
            std::cout << x << ' ' << x << ' ';
        }
    } else {
        int x = rand(1, n);
        std::cout << x << ' ';
        for (int i = 1; i <= d / 2; i += 1) {
            std::cout << x << ' ' << x << ' ';
        }
    }

    std::cout << '\n';

    // all random
    // constexpr int Kn = 888;
    // std::cout << Kn << '\n';
    // std::vector<int>p(Kn + 1);
    // std::ranges::iota(p, 0);
    // std::shuffle(p.begin() + 1, p.end(), rng);
    // std::shuffle(p.begin() + 1, p.end(), rng);
    // std::shuffle(p.begin() + 1, p.end(), rng);
    // std::shuffle(p.begin() + 1, p.end(), rng);
    // std::shuffle(p.begin() + 1, p.end(), rng);
    // std::shuffle(p.begin() + 1, p.end(), rng);
    // std::shuffle(p.begin() + 1, p.end(), rng);
    // std::shuffle(p.begin() + 1, p.end(), rng);
    // std::shuffle(p.begin() + 1, p.end(), rng);
    // std::shuffle(p.begin() + 1, p.end(), rng);
    // std::shuffle(p.begin() + 1, p.end(), rng);
    // std::shuffle(p.begin() + 1, p.end(), rng);
    // std::shuffle(p.begin() + 1, p.end(), rng);
    // std::shuffle(p.begin() + 1, p.end(), rng);
    // std::shuffle(p.begin() + 1, p.end(), rng);
    // std::shuffle(p.begin() + 1, p.end(), rng);
    // std::shuffle(p.begin() + 1, p.end(), rng);
    // std::shuffle(p.begin() + 1, p.end(), rng);
    // for (int i = 1; i <= Kn; i += 1) {
    //     std::cout << p[i] << ' ';
    // }
    // std::cout << '\n';

    // 

    return 0;
}