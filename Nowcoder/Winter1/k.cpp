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
		int k = r - l + 1;
		k = std::__lg(k);
		return jump[k][l] + jump[k][r - (1 << k) + 1];
	}
};

struct GCD {
    int val = 0;
    constexpr friend GCD operator+(const GCD& a, const GCD& b) {
        return {std::gcd(a.val, b.val)};
    }
};

// struct Node {
//     Node* ch[2] = {nullptr, nullptr};
//     int cnt = 0;
// };

// void add(Node*& t, int l, int r, int x) {
//     if (t == nullptr) {
//         t = new Node;
//     }
//     t->cnt += 1;
//     if (l == r) {
//         return ;
//     }
//     i64 mid = (l + r) >> 1;
//     if (x <= mid) {
//         add(t->ch[0], l, mid, x);
//     } else {
//         add(t->ch[1], mid + 1, r, x);
//     }
// }

// Node* merge(Node* a, Node* b, int l, int r) {
//     if (a == nullptr) {
//         return b;
//     }
//     if (b == nullptr) {
//         return a;
//     }
//     Node* c = new Node;
//     if (l == r) {
//         c->cnt = a->cnt + b->cnt;
//         return c;
//     }
//     i64 mid = (l + r) >> 1;
//     c->ch[0] = merge(a->ch[0], b->ch[0], l, mid);
//     c->ch[1] = merge(a->ch[1], b->ch[1], mid + 1, r);
//     c->cnt = (c->ch[0] == nullptr ? 0 : c->ch[0]->cnt) + (c->ch[1] == nullptr ? 0 : c->ch[1]->cnt);
//     return c;
// }

// int query(Node*& t, int l, int r, int x) {
//     if (t == nullptr) {
//         return 0;
//     }
//     if (l == r) {
//         return t->cnt;
//     }
//     int mid = (l + r) >> 1;
//     if (x <= mid) {
//         return query(t->ch[0], l, mid, x);
//     } else {
//         return query(t->ch[1], mid + 1, r, x);
//     }
// }

// constexpr int Kn = 1E5;
// struct Node {
//     int ch[2] {};
//     int cnt = 0;
// }info[Kn << 5];

// int tot = 0;
// void add(int& now, int pre, int x, int k) {
//     info[now = ++tot] = info[pre];
//     info[now].cnt += 1;
//     if (k < 0) {
//         return ;
//     }
//     debug(tot);
//     add(info[now].ch[x >> k & 1], info[pre].ch[x >> k & 1], x, k - 1);
// }

// int query(int l, int r, int x) {
//     for (int k = 30; k >= 0; k -= 1) {
//         l = info[l].ch[x >> k & 1];
//         r = info[r].ch[x >> k & 1];
//     }
//     return info[r].cnt - info[l].cnt;
// }

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto solve = [&]() {
        int n;
        std::cin >> n;

        std::vector<int>a(n + 1);
        for (int i = 1; i <= n; i += 1) {
            std::cin >> a[i];
        }

        auto g = SparseTable<GCD>(a);
        std::vector<int>s(n + 1);
        for (int i = 1; i <= n; i += 1) {
            s[i] = s[i - 1] ^ a[i];
        }

        std::map<int, std::vector<int>>rec;
        for (int i = 1; i <= n; i += 1) {
            rec[s[i]].push_back(i);
        }

        i64 res = 0;
        for (int l = 1; l <= n - 1; l += 1) {
            for (int r = l + 1; r <= n;) {
                int cur = g.range(l, r).val;
                int lo = r, hi = n;
                while (lo <= hi) {
                    int mid = (lo + hi) >> 1;
                    if (g.range(l, mid).val == cur) {
                        lo = mid + 1;
                    } else {
                        hi = mid - 1;
                    }
                }
                int y = cur ^ s[l - 1];
                int h = lo - 1;
                if (rec.contains(y)) {
                    res += std::ranges::upper_bound(rec[y], h) - std::ranges::lower_bound(rec[y], r);
                }
                r = h + 1;
            }
        }

        std::cout << res << '\n';
    };

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}