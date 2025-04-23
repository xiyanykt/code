#include<bits/stdc++.h>

using i64 = long long;

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int rand(int l, int r) {
    return std::uniform_int_distribution<int>(l, r)(rng);
}

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cout << 1 << "\n";

    constexpr int N = 1E5;
    constexpr int K = 2;

    std::cout << N << " " << K << "\n";
    for (int i = 1; i <= N; i += 2) {
        std::cout << i << " " << i << " ";
    }


    return 0;
}