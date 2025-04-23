#include "W:\v\algo\xoxo.hpp"
#include "W:\v\algo\fast_io.hpp"
#include "W:\v\algo\datastructure\segtree.hpp"

constexpr i64 inf = 1E17;
struct Info {
	i64 maxl = -inf;
	i64 minl = inf;
	i64 maxr = -inf;
	i64 minr = inf;
	i64 res = -inf;
	Info () {

	}

	Info (int x, int i) {
		maxr = x - i;
		minl = x - i;
		maxl = x + i;
		minr = x + i;
		res = 0;
	}
};

Info operator+(const Info& a, const Info& b) {
	Info c {};
	c.maxl = max(a.maxl, b.maxl);
	c.maxr = max(a.maxr, b.maxr);
	c.minl = min(a.minl, b.minl);
	c.minr = min(a.minr, b.minr);
	c.res = max({a.res, b.res, b.maxr - a.minl, a.maxl - b.minr});
	return c;
}

auto solve() {
	int n, q;
	cin >> n >> q;

	vector<int>a(n + 1);
	for (int i = 1; i <= n; i += 1) {
		cin >> a[i];
	}

	SegmentTree<Info>seg(n);
	for (int i = 1; i <= n; i += 1) {
		seg.modify(i, Info(a[i], i));
	}

	cout << seg.info[1].res << '\n';
	while (q--) {
		int i, x;
		cin >> i >> x;
		a[i] = x;
		seg.modify(i, Info(a[i], i));
		cout << seg.info[1].res << '\n';
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