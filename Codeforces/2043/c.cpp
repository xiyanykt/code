#include "algo\xoxo.hpp"
#include "algo\fast_io.hpp"

auto solve() {
	int n;
	cin >> n;

	vector<int>a(n);
	for (auto & ai : a) {
		cin >> ai;
	}

	auto f = [&](const vector<int> & a) {
		int sum = 0, mn = 0, mx = 0, mnp = 0, mxp = 0;
		for (const auto & ai : a) {
			sum += ai;
			chmin(mnp, sum);
			chmax(mxp, sum);
			chmin(mn, sum - mxp);
			chmax(mx, sum - mnp);
		}
		return pair(mn, mx);
	};

	auto g = [&](const auto & a) {
		int sum = 0, mnp = 0, mxp = 0;
		for (const auto & ai : a) {
			sum += ai;
			chmin(mnp, sum);
			chmax(mxp, sum);
		}
		return pair(mnp, mxp);
	};

	auto it = ranges::find_if(a, [](const int& x) {
		return x != 1 && x != -1;
	});
	if (it == a.end()) {
		auto [l, r] = f(a);
		cout << (r - l + 1) << '\n';
		for (const auto & e : views::iota(l, r + 1)) {
			cout << e << ' ';
		}
		cout << '\n';
	} else {
		set<int>rec;
		{
			auto [l , r] = f({a.begin(), it});
			for (const int & x : views::iota(l, r + 1)) {
				rec.insert(x);
			}
		}
		{
			auto [l, r] = f({next(it), a.end()});
			for (const int & x : views::iota(l, r + 1)) {
				rec.insert(x);
			}
		}
		auto [l1, r1] = g(vector(a.begin(), it) | views::reverse);
		auto [l2, r2] = g(vector(next(it), a.end()));
		for (const auto & x : views::iota(*it + l1 + l2, *it + r1 + r2 + 1)) {
			rec.insert(x);
		}
		cout << rec.size() << '\n';
		for (const auto & e : rec) {
			cout << e << ' ';
		}
		cout << '\n';
	}
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