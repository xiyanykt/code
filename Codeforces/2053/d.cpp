#include "W:\v\algo\xoxo.hpp"
#include "W:\v\algo\fast_io.hpp"
#include "W:\v\algo\math\modint.hpp"

constexpr int Mod = 998244353;
using Z = ModInt<Mod>;

#include<bits/extc++.h>
using namespace __gnu_pbds;

template<class KT, class VT = null_type>
using RBT = tree<KT, VT, std::less<KT>, rb_tree_tag, tree_order_statistics_node_update>;

auto solve() {
	int n, q;
	cin >> n >> q;

	vector<int>a(n + 1), b(n + 1);
	for (int i = 1; i <= n; i += 1) {
		cin >> a[i];
	}

	for (int i = 1; i <= n; i += 1) {
		cin >> b[i];
	}

	RBT<pair<int, int>>sa, sb;
	for (int i = 1; i <= n; i += 1) {
		sa.insert({a[i], i});
		sb.insert({b[i], i});
	}

	Z res = 1;
	for (int i = 1; i <= n; i += 1) {
		res *= min(sa.find_by_order(i - 1)->first, sb.find_by_order(i - 1)->first);
	}

	auto f = [&](auto & a, auto & sa, auto & sb, int p) {
		auto it = sa.upper_bound({a[p], n + 1});
		int i = it == sa.end() ? n - 1 : sa.order_of_key(*it) - 1;
		int x = sa.find_by_order(i)->first;
		int y = sb.find_by_order(i)->first;
		res /= min(x, y);
		res *= min(x + 1, y);
		sa.erase({a[p], p});
		a[p] += 1;
		sa.insert({a[p], p});
	};

	cout << res .val() << ' ';
	while (q--) {
		int o, p;
		cin >> o >> p;
		if (o == 1) {
			f(a, sa, sb, p);
		} else {
			f(b, sb, sa, p);
		}
		cout << res.val() << ' ';
	}
	cout << "\n";
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