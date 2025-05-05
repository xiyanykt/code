#include<bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f64 = long double;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

#ifndef ONLINE_JUDGE
#include "algo/debug.hpp"
#else
#define debug(...) (void)13
#endif

template<class T>
constexpr bool chmax (T& x, T y) {
    if (y > x) {
        x = y;
        return true;
    }
    return false;
}

template<class T>
constexpr bool chmin (T& x, T y) {
    if (y < x) {
        x = y;
        return true;
    }
    return false;
}

struct SAM {
    static constexpr int ALPHABET = 26;
    struct Node {
        int len;
        int link;
        std::array<int, ALPHABET>next;
        Node(): len{}, link{}, next{} {}
    };

    std::vector<Node> t;
    int dfn;
    std::vector<int>end;
    std::vector<std::vector<int>>adj;
    std::vector<int>lo, hi;
    SAM() {
        t.assign(2, Node());
        t[0].next.fill(1);
        t[0].len = -1;
    }

    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }

    int extend(int p, int x) {
        if (t[p].next[x]) {
            int q = t[p].next[x];
            if (t[q].len == t[p].len + 1) {
                return q;
            }
            int r = newNode();
            t[r].len = t[p].len + 1;
            t[r].link = t[q].link;
            t[r].next = t[q].next;
            t[q].link = r;
            while (t[p].next[x] == q) {
                t[p].next[x] = r;
                p = t[p].link;
            }
            return r;
        }
        int cur = newNode();
        t[cur].len = t[p].len + 1;
        while (not t[p].next[x]) {
            t[p].next[x] = cur;
            p = t[p].link;
        }
        t[cur].link = extend(p, x);
        return cur;
    }

    int next(int p, int x) {
        return t[p].next[x];
    }

    int link(int p) {
        return t[p].link;
    }

    int len(int p) {
        return t[p].len;
    }

    int size() {
        return t.size();
    }

    SAM(const std::string& s) {
        t.assign(2, Node());
        t[0].next.fill(1);
        t[0].len = -1;
        int p = 1;
        end = {};
        for (char c : s) {
            p = extend(p, c - 'a');
            end.push_back(p);
        }

        adj.assign(size(), {});
        for (int i = 2; i < size(); i += 1) {
            adj[link(i)].push_back(i);
        }

        dfn = 0;
        lo.assign(size(), 0);
        hi.assign(size(), 0);
        auto dfs = [&](auto && self, int u) ->void {
            lo[u] = ++dfn;
            for (int v : adj[u]) {
                self(self, v);
            }
            hi[u] = dfn;
        };
        dfs(dfs, 1);
    }

    auto work(const std::string& t) {
        int p = 1;
        std::vector<int>r(t.size(), -1);
        for (int i = 0; i < t.size(); i += 1) {
            p = next(p, t[i] - 'a');
            if (!p) {
                break;
            }
            r[i] = p;
        }
        return r;
    }
};

template<typename T>
struct Fenwick {
	int n;
	std::vector<T>a;
    Fenwick() = default;
    Fenwick(int n): n{n}, a(n + 1, T{}) {}

	void add(int p, const T& x) {
		if (p >= 1 && p <= n) {
			for (int i = p; i <= n; i += i & -i) {
				a[i] += x;
			}
		}
	}

	T sum(int p) {
		T ans = T();
		if (p >= 1 && p <= n) {
			for (int i = p; i > 0; i -= i & -i) {
				ans += a[i];
			}
		}
		return ans;
	}

	T rangeQuery(int l, int r) {
		return sum(r) - sum(l - 1);
	}

	int select(int k) {
		int x = 0;
		T cur = T();
		for (int i = std::__lg(n); ~i; i -= 1) {
			x += 1 << i;
			if (x >= n or cur + a[x] >= k) {
				x -= 1 << i;
			} else {
				cur = cur + a[x];
			}
		}
		return x + 1;
	}
};

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string s1, s2;
    std::cin >> s1 >> s2;

    auto sam1 = SAM(s1);
    std::reverse(s2.begin(), s2.end());
    auto sam2 = SAM(s2);

    int n = s1.size();
    std::vector<std::vector<int>>e(sam1.size());
    for (int i = 0; i + 1 < n; i += 1) {
        int u1 = sam1.end[i];
        int u2 = sam2.end[n - i - 2];
        e[sam1.lo[u1]].push_back(sam2.lo[u2]);
    }

    int q;
    std::cin >> q;
    std::vector<std::vector<std::array<int, 3>>>g(sam1.size());
    for (int c = 1; c <= q; c += 1) {
        std::string t;
        std::cin >> t;
        auto ends1 = sam1.work(t);
        std::reverse(t.begin(), t.end());
        auto ends2 = sam2.work(t);
        for (int i = 0; i + 1 < t.size(); i += 1) {
            if (ends1[i] == -1 || ends2[t.size() - i - 2] == -1) {
                continue;
            }
            int l1 = sam1.lo[ends1[i]], r1 = sam1.hi[ends1[i]];
            int l2 = sam2.lo[ends2[t.size() - i - 2]], r2 = sam2.hi[ends2[t.size() - i - 2]];
            g[r1].push_back({r2, 1, c});
            g[r1].push_back({l2 - 1, -1, c});
            g[l1 - 1].push_back({l2 - 1, 1, c});
            g[l1 - 1].push_back({r2, -1, c});
        }
    }

    std::vector<i64>res(q + 1);
    Fenwick<i64>fen(sam2.size());
    for (int i = 0; i < sam1.size(); i += 1) {
        for (int y : e[i]) {
            fen.add(y, 1);
        }
        for (auto [v, coef, q] : g[i]) {
            res[q] += fen.sum(v) * coef;
        }
    }

    for (int i = 1; i <= q; i += 1) {
        std::cout << res[i] << '\n';
    }
    return 0;
}
