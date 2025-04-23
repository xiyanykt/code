#include "algo\xoxo.hpp"
// #include "algo\fast_io.hpp"

auto solve() {
	i64 n;
	int d;
	cin >> n >> d;

	vector<int>r {1};
	int v = n % 9;
	i64 p = 1;
	for (int i = 1; i <= v; i += 1) {
		p *= i;
	}

	if ((p * d) % 9 == 0 || n >= 6) {
		r.push_back(9);
	}

	v = n % 3;
	p = 1;
	for (int i = 1; i <= v; i += 1) {
		p *= i;
	}
	if ((p * d) % 3 == 0 || n >= 3) {
		r.push_back(3);
	}

	if (d == 5) {
		r.push_back(5);
	}

	if (d == 7 || n >= 3) {
		r.push_back(7);
	}

	ranges::sort(r);
	for (const auto & c : r) {
		cout << c << ' ';
	}
	cout << '\n';
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