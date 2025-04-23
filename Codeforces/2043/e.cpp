#include "W:\v\algo\xoxo.hpp"
#include "W:\v\algo\fast_io.hpp"

auto solve() {
	int n, m;
	cin >> n >> m;

	vector a(n, vector<int>(m)), b(n, vector<int>(m));
	for (auto & ai : a) {
		for (auto & aij : ai) {
			cin >> aij;
		}
	}

	for (auto & bi : b) {
		for (auto & bij : bi) {
			cin >> bij;
		}
	}

	constexpr int Kn = 30;
	auto work = [&]() {
		for (int j : views::iota(0, m)) {
			for (int k : views::iota(0, Kn)) {
				if (ranges::any_of(views::iota(0, n), [&](int i) {
				return ((~a[i][j] >> k & 1) && (b[i][j] >> k & 1));
				})) {
					for (int i : views::iota(0, n)) {
						if (~a[i][j] >> k & 1) {
							a[i][j] |= 1 << k;
						}
					}
				}
			}
		}

		for (int i : views::iota(0, n)) {
			for (int k : views::iota(0, Kn)) {
				if (ranges::any_of(views::iota(0, m), [&](int j) {
				return ((a[i][j] >> k & 1) && (~b[i][j] >> k & 1));
				})) {
					for (int j : views::iota(0, m)) {
						if (a[i][j] >> k & 1) {
							a[i][j] ^= 1 << k;
						}
					}
				}
			}
		}
	};

	auto vaild = [&]() {
		return ranges::all_of(views::iota(0, n), [&](int i) {
			return ranges::all_of(views::iota(0, m), [&](int j) {
				return a[i][j] == b[i][j];
			});
		});
	};

	for (int _ : views::iota(0, 2)) {
		if (vaild()) {
			cout << "YES\n";
			return ;
		}
		work();
	}

	cout << "NO\n";
}

auto main() -> int {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t = 1;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}