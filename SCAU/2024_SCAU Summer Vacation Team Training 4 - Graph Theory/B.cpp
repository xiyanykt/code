#include <bits/stdc++.h>

using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;

#ifndef ONLINE_JUDGE
#include "algo\debug.hpp"
#else
#define debug(...) (void)42
#endif

constexpr int dx[4] = {0, 0, 1, -1};
constexpr int dy[4] = {1, -1, 0, 0};

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cout << std::fixed << std::setprecision(13);

	int W, H, P;
	while (true) {
		std::cin >> W >> H >> P;

		if (W == 0 and H == 0 and P == 0) {
			break;
		}

		// std::swap(W, H);

		std::vector A(H + 1, std::vector<int>(W + 1));
		for (int i = 1; i <= H; i += 1) {
			for (int j = 1; j <= W; j += 1) {
				std::cin >> A[i][j];
			}
		}

		std::queue<std::array<int, 2>> Q;
		std::vector vis(H + 1, std::vector<int>(W + 1));
		for (int i = 1; i <= P; i += 1) {
			int X, Y;
			std::cin >> X >> Y;
			std::swap(X, Y);
			X += 1, Y += 1;
			vis[X][Y] = 1;
			Q.push({X, Y});
		}

		while (not Q.empty()) {
			auto [X, Y] = Q.front();
			Q.pop();
			for (int j = 0; j <= 3; j += 1) {
				int nX = X + dx[j], nY = Y + dy[j];
				if (nX >= 1 and nX <= H and nY >= 1 and nY <= W and not vis[nX][nY] and A[X][Y] > A[nX][nY]) {
					vis[nX][nY] = 1;
					Q.push({nX, nY});
				}
			}
		}

		int ans = 0;
		for (int i = 1; i <= H; i += 1) {
			for (int j = 1; j <= W; j += 1) {
				ans += vis[i][j];
			}
		}

		std::cout << ans << "\n";
	}

	return 0;
}