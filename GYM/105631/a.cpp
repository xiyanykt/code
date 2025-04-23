#include "W:\v\algo\xoxo.hpp"
#include "W:\v\algo\fast_io.hpp"

auto solve() {
	int a, b, c;
	cin >> a >> b >> c;
	cout << min({a / 2, b, c}) << '\n';
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