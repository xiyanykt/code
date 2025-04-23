#include<bits/stdc++.h>

using i64 = int64_t;

#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) (void)42
#endif

struct Q {
	int l, r, e;
};

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, q;
	std::cin >> n >> q;

	std::vector<int>a(n + 1);
	for (int i = 1; i <= n; i += 1) {
		std::cin >> a[i];
	}

	const int B = std::sqrt(n);
	std::vector<int>belong(n + 1);
	for (int i = 1; i <= n; i += 1) {
		belong[i] = (i - 1) / B + 1;
	}

	std::vector<Q>qry;
	qry.push_back({});
	std::vector<int>ans(q + 1, -1);

	constexpr int N = 1E6 + 1;

	for (int i = 1; i <= q; i += 1) {
		char o;
		std::cin >> o;
		if (o == 'Q') {
			int l, r;
			std::cin >> l >> r;
			qry.push_back({l, r, i});
		} else {
			int p, x;
			std::cin >> p >> x;
			if (qry.size() == 1) {
				;
			} else {
				int res = 0;
				std::vector<int>cnt(N + 1);
				std::sort(qry.begin() + 1, qry.end(), [&](const auto & x, const auto & y) {
					if (belong[x.l] ^ belong[y.l]) {
						return belong[x.l] < belong[y.l];
					} else if (belong[x.l] & 1) {
						return x.r < y.r;
					}
					return x.r > y.r;
				});

				auto add = [&](int p) {
					if (cnt[a[p]] == 0) {
						res += 1;
					}
					cnt[a[p]] += 1;
				};
				auto del = [&](int p) {
					cnt[a[p]] -= 1;
					if (cnt[a[p]] == 0) {
						res -= 1;
					}
				};
				int l = 1, r = 0;
				for (int j = 1; j < (int)qry.size(); j += 1) {
					while (l < qry[j].l) {
						del(l++);
					}
					while (l > qry[j].l) {
						add(--l);
					}
					while (r < qry[j].r) {
						add(++r);
					}
					while (r > qry[j].r) {
						del(r--);
					}
					ans[qry[j].e] = res;
				}
			}
			a[p] = x;
			qry.clear();
			qry.push_back({});
		}
	}

	if (qry.size() != 1) {
		int res = 0;
		std::vector<int>cnt(N + 1);
		std::sort(qry.begin() + 1, qry.end(), [&](const auto & x, const auto & y) {
			if (belong[x.l] ^ belong[y.l]) {
				return belong[x.l] < belong[y.l];
			} else if (belong[x.l] & 1) {
				return x.r < y.r;
			}
			return x.r > y.r;
		});

		auto add = [&](int p) {
			if (cnt[a[p]] == 0) {
				res += 1;
			}
			cnt[a[p]] += 1;
		};
		auto del = [&](int p) {
			cnt[a[p]] -= 1;
			if (cnt[a[p]] == 0) {
				res -= 1;
			}
		};
		int l = 1, r = 0;
		for (int j = 1; j < (int)qry.size(); j += 1) {
			while (l < qry[j].l) {
				del(l++);
			}
			while (l > qry[j].l) {
				add(--l);
			}
			while (r < qry[j].r) {
				add(++r);
			}
			while (r > qry[j].r) {
				del(r--);
			}
			ans[qry[j].e] = res;
		}
	}

	for (int i = 1; i <= q; i += 1) {
		if (ans[i] != -1) {
			std::cout << ans[i] << "\n";
		}
	}

	return 0;
}