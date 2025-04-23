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
    int cnt = 0;
    std::array<int, Kn> next {};
};

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    int maxlen = 0;
    std::vector<std::string>s(n + 1);
    for (int i = 1; i <= n; i += 1) {
        std::cin >> s[i];
        maxlen = std::max(maxlen, int(s[i].length()));
    }

    std::vector<Node>t;
    t.assign(2, {});

    auto newNode = [&]() {
        t.emplace_back();
        return t.size() - 1;
    };

    for (int i = 1; i <= n; i += 1) {
        int p = 1;
        for (const auto & c : s[i]) {
            if (!t[p].next[c - 'a']) {
                t[p].next[c - 'a'] = newNode();
            }
            p = t[p].next[c - 'a'];
            t[p].cnt += 1;
        }
        t[p].cnt += 1;
    }

    while (q--) {
        int l, r;
        std::cin >> l >> r;

        i64 res = 2 * (t.size() - 2) - maxlen;
        std::cout << res << '\n';
    }

   return 0;
}