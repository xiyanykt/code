#include "W:\v\algo\xoxo.hpp"
#include "W:\v\algo\fast_io.hpp"

auto solve() {
	int n, k;
	cin >> n >> k;

	vector<int>a(n + 1);
	for (int i = 1; i <= n; i += 1) {
		cin >> a[i];
	}

	map<int, int>rec;
	for (int i = 1; i <= n; i += 1) {
		rec[a[i]] += 1;
	}

	vector<int>c;
	for (const auto & [x , v] : rec) {
		c.push_back(v);
	}

	int r = c.size();
	ranges::sort(c);
	for (int i = 0; i < c.size(); i += 1) {
		if (k < c[i]) {
			break;
		}
		r -= 1;
		k -= c[i];
	}

	cout << max(1, r) << '\n';
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