#include <bits/stdc++.h>
using namespace std;
#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...) (void)0
#endif
using i64 = int64_t;
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int n;
	cin >> n;
	vector<pair<int, int>> p;
	map<int, int> count;
	for (int i = 0, a, b; i < n; i += 1) {
		cin >> a >> b;
		if (a == b) count[a] += 1;
		if (a > b) swap(a, b);
		if (a < b) p.emplace_back(a, b);
	}
	sort(p.begin(), p.end());
	for (auto& [a, b] : p) swap(a, b);

	set<pair<int, int>, greater<pair<int, int>>> sp;
	for (auto [x, y] : count) sp.emplace(y, x);
	while (not sp.empty()) {
		int err = 1;
		p.emplace_back(0, 0);
		debug(p, sp);
		vector<pair<int, int>> q;
		int last = 0;
		for (auto [a, b] : p) {
			while (true) {
				int done = 1;
				for (auto it = sp.begin(); it != sp.end(); it = next(it)) {
					auto [x, y] = *it;
					if (y != last and y != a) {
						sp.erase(it);
						last = y;
						q.emplace_back(y, y);
						if (x > 1) sp.emplace(x - 1, y);
						err = 0;
						done = 0;
						break;
					}
				}
				if (done) break;
			}
			q.emplace_back(a, b);
			last = b;
		}
		q.pop_back();
		p.swap(q);
		if (err) {
			cout << "No";
			return 0;
		}
	}
	cout << "Yes\n";
	for (auto [x, y] : p) cout << x << " " << y << "\n";
}