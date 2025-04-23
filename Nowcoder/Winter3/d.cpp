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
#define debug(...) (void)42
#endif

template<class T>
constexpr bool chmax(T& x, T y) {
    if (y > x) {
        x = y;
        return true;
    }
    return false;
}

template<class T>
constexpr bool chmin(T& x, T y) {
    if (y < x) {
        x = y;
        return true;
    }
    return false;
}

template <class Info>
struct SparseTable {
	std::vector<std::vector<Info>>jump;

	SparseTable() = default;
	constexpr SparseTable(const auto& a) {
		int n = a.size() - 1;
		int logn = std::__lg(n);
		jump.assign(logn + 1, std::vector<Info>(n + 1, Info()));
		for (int i = 0; i <= n; i += 1) {
			jump[0][i] = Info(a[i]);
		}
		for (int j = 1; j <= logn; j += 1) {
			for (int i = 1; i + (1 << (j - 1)) - 1 <= n; i += 1) {
				jump[j][i] = jump[j - 1][i] + jump[j - 1][i + (1 << (j - 1))]; 
			}
		}
	}

	constexpr Info range(int l, int r) const {
		if (l > r || l < 1 || r > jump[0].size() - 1) {
			return Info();
		}
		int k = r - l + 1;
		k = std::__lg(k);
		return jump[k][l] + jump[k][r - (1 << k) + 1];
	}
};

struct Max {
    int val = 0;
    constexpr friend Max operator+(const Max& a, const Max& b) {
        return {std::max(a.val, b.val)};
    }
};

template<typename T>
struct Fenwick {
	int n;
	std::vector<T>a;

	Fenwick() {

	}
	
	Fenwick(int n) {
		this->n = n;
		a.assign(n + 1, T());
	}

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

constexpr int Kn = 26;
struct Node {
    std::vector<int> v {};
    std::array<int, Kn> next {};
};

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<std::string>s(n + 1);
    for (int i = 1; i <= n; i += 1) {
        std::cin >> s[i];
    }

    std::vector<int>v(n + 1);
    for (int i = 1; i <= n; i += 1) {
        v[i] = s[i].length();
    }

    auto f = SparseTable<Max>(v);

    std::vector<Node>t;
    t.assign(2, {});

    auto newNode = [&]() {
        t.emplace_back();
        return t.size() - 1;
    };

    Fenwick<int>fen(n);
    for (int i = 1; i <= n; i += 1) {
        int p = 1;
        for (const auto & c : s[i]) {
            if (!t[p].next[c - 'a']) {
                fen.add(i, 1);
                t[p].next[c - 'a'] = newNode();
            }
            p = t[p].next[c - 'a'];
            t[p].v.push_back(i);
        }
    }

    for (int i = 2; i < t.size(); i += 1) {
        std::ranges::reverse(t[i].v);
    }

    std::vector<std::vector<std::pair<int, int>>>qry(n + 1);
    for (int i = 1; i <= q; i += 1) {
        int l, r;
        std::cin >> l >> r;
        qry[l].push_back({r, i});
    }

    std::vector<i64>res(q + 1);
    for (int l = 1; l <= n; l += 1) {
        for (const auto & [r, i] : qry[l]) {
            res[i] = 2LL * fen.rangeQuery(l, r) - f.range(l, r).val;
        }
        int p = 1;
        for (const auto & c : s[l]) {
            p = t[p].next[c - 'a'];
            fen.add(l, -1);
            t[p].v.pop_back();
            if (!t[p].v.empty()) {
                fen.add(t[p].v.back(), 1);
            }
        }
    }

    for (int i = 1; i <= q; i += 1) {
        std::cout << res[i] << "\n";
    }

   return 0;
}