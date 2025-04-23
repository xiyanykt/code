#include<bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f64 = long double;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

#include"W:\v\algo\debug.hpp"
#include"W:\v\algo\Datastruct.hpp"

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

constexpr int inf = 1E9;
struct Info {
	int val = 0;

	Info() {

	}

	Info(const int & x) : val(x) {

	}
};

Info operator+(const Info &a, const Info &b) {
	return {std::max(a.val, b.val)};
}

auto main() ->int32_t {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	auto solve = [&]() {
		int n;
		std::cin >> n;

		std::vector<int>w(n + 1);
		for (int i = 1; i <= n; i += 1) {
			std::cin >> w[i];
		}

		int r = 0;
		SegmentTree<Info>seg(n);
		for (int i = 1; i <= n; i += 1) {
			seg.modify(i, {w[i]});
		}

		for (int i = n; i >= 1; i -= 1) {
			int j = seg.findLast(1, i - 1, [&](const Info & e) {
				return e.val >= w[i];
			});
			if (j == -1) {
				chmax(r, i - 1);
				break;
			} else {
				chmax(r, i - j - 1);
				i = j + 1;
			}
		}
		std::cout << r << '\n';
	};

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}