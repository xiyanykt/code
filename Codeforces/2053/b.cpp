#include "W:\v\algo\xoxo.hpp"
#include "W:\v\algo\fast_io.hpp"
#include "W:\v\algo\datastructure\fenwick.hpp"

auto solve() {
	int n;
	cin >> n;

	vector<int>l(n + 1), r(n + 1);
	for (int i = 1; i <= n; i += 1) {
		cin >> l[i] >> r[i];
	}

	map<int, int>rec;
	Fenwick<int>fen(2 * n);
	for (int i = 1; i <= n; i += 1) {
		if (l[i] == r[i]) {
			rec[l[i]] += 1;
			if (rec[l[i]] == 1) {
				fen.add(l[i], 1);
			}
		}
	}

	for (int i = 1; i <= n; i += 1) {
		if (l[i] == r[i]) {
			rec[l[i]] -= 1;
			if (rec[l[i]] == 0) {
				fen.add(l[i], -1);
			}
		}
		if (fen.range(l[i], r[i])  >= r[i] - l[i] + 1) {
			cout << 0;
		} else {
			cout << 1;
		}
		if (l[i] == r[i]) {
			rec[l[i]] += 1;
			if (rec[l[i]] == 1) {
				fen.add(l[i], 1);
			}
		}
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