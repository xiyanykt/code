#include "W:\v\algo\xoxo.hpp"
#include "W:\v\algo\fast_io.hpp"

auto solve() {
	int n;
	cin >> n;

	vector<int>a(n + 1);
	for (int i = 1; i <= n; i += 1) {
		cin >> a[i];
	}

	for (int i = 2; i <= n; i += 1) {
		if (a[i] < 2 * a[i - 1] && 2 * a[i] > a[i - 1]) {
			debug('A', i);
			cout << "YES\n";
			return ;
		}
	}

	for (int i = 1; i <= n - 1; i += 1) {
		if (a[i] < 2 * a[i + 1] && 2 * a[i] > a[i + 1]) {
			debug('B', i);
			cout << "YES\n";
			return ;
		}
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