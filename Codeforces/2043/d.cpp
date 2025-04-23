#include "W:\v\algo\xoxo.hpp"
#include "W:\v\algo\fast_io.hpp"

auto solve() {
	i64 l, r, g;
	cin >> l >> r >> g;

	l = (l + g - 1) / g;
	r = r / g;
	for (i64 k = r - l; k >= 0; k -= 1) {
		for (i64 i = l; i + k <= r; i += 1) {
			if (gcd(i, i + k) == 1) {
				cout << i * g << ' ' << (i + k) * g << '\n';
				return ;
			}
		}
	}

	cout << -1 << ' ' << -1 << '\n';
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