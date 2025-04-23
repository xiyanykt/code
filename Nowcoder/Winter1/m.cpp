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

template<class Info>
struct SegmentTree {
    int n;
    std::vector<Info>info;

    SegmentTree() {
        
    }

    SegmentTree(const int & n) {
        this->n = n;
        info.assign(4 << std::__lg(n), Info());
    }

    SegmentTree(const std::vector<Info>& a) {
        int n = a.size() - 1;
        this->n = n;
        info.assign(4 << std::__lg(n), Info());
        auto work = [&](auto && self, int p, int l, int r) {
            if (l == r) {
                info[p] = Info(a[l]);
                return;
            }
            int mid = (l + r) >> 1;
            self(self, p << 1, l, mid), self(self, p << 1 | 1, mid + 1, r);
            info[p] = info[p << 1] + info[p << 1 | 1];
        };
        work(work, 1, 1, n);
    }

    void modify(int p, int l, int r, int L, int R, const Info& v) {
        if (l > R or r < L) {
            return;
        }
        if (L <= l and r <= R) {
            info[p] = v;
            return;
        }
        int mid = (l + r) >> 1;
        modify(p << 1, l, mid, L, R, v), modify(p << 1 | 1, mid + 1, r, L, R, v);
        info[p] = info[p << 1] + info[p << 1 | 1];
    }
    void modify(int p, const Info& v) {
        modify(1, 1, n, p, p, v);
    }

    Info rangeQuery(int p, int l, int r, int L, int R) {
        if (l > R or r < L) {
            return Info();
        }
        if (L <= l and r <= R) {
            return info[p];
        }
        int mid = (l + r) >> 1;
        return rangeQuery(p << 1, l, mid, L, R) + rangeQuery(p << 1 | 1, mid + 1, r, L, R);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 1, n, l, r);
    }

    template<class F>
    int findFirst(int p, int l, int r, int L, int R, F pred) {
        if (l > R or r < L or not pred(info[p])) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        int mid = (l + r) >> 1;
        int res = findFirst(p << 1, l, mid, L, R, pred);
        return res == -1 ? findFirst(p << 1 | 1, mid + 1, r, L, R, pred) : res;
    }
    template<class F>
    int findFirst(int l, int r, F pred) {
        return findFirst(1, 1, n, l, r, pred);
    }

    template<class F>
    int findLast(int p, int l, int r, int L, int R, F pred) {
        if (l > R or r < L or not pred(info[p])) {
            return -1;
        }
        if (l == r) {
            return r;
        }
        int mid = (l + r) >> 1;
        int res = findLast(p << 1 | 1, mid + 1, r, L, R, pred);
        return res == -1 ? findLast(p << 1, l, mid, L, R, pred) : res;
    }
    template<class F>
    int findLast(int l, int r, F pred) {
        return findLast(1, 1, n, l, r, pred);
    }

    template<class F>
    int findPrefixFirst(int p, int l, int r, int L, int R, const F& pred, Info& pref) {
        if (l > R or r < L) {
            return r + 1;
        }
        if (L <= l and r <= R) {
            if (not pred(pref + info[p])) {
                pref = pref + info[p];
                return r + 1;
            }
            if (l == r) {
                return l;
            }
            int mid = (l + r) >> 1;
            int res;
            if (pred(pref + info[p << 1])) {
                res = findPrefixFirst(p << 1, l, mid, L, R, pred, pref);
            } else {
                pref = pref + info[p << 1];
                res = findPrefixFirst(p << 1 | 1, mid + 1, r, L, R, pred, pref);
            }
            return res;
        }
        int mid = (l + r) >> 1;
        int res = mid + 1;
        if (L <= mid) {
            res = findPrefixFirst(p << 1, l, mid, L, R, pred, pref);
        }
        if (res == mid + 1 and mid + 1 <= R) {
            res = findPrefixFirst(p << 1 | 1, mid + 1, r, L, R, pred, pref);
        }
        return res;
    }
    template<class F>
    int findPrefixFirst(int l, int r, const F& pred) {
        Info pref = Info();
        int res = findPrefixFirst(1, 1, n, l, r, pred, pref);
        return res == r + 1 ? -1 : res;
    }

    template<class F>
    int findSurfixLast(int p, int l, int r, int L, int R, const F& pred, Info& surf) {
        if (l > R or r < L) {
            return l - 1;
        }
        if (L <= l and r <= R) {
            if (not pred(surf + info[p])) {
                surf = surf + info[p];
                return l - 1;
            }
            if (l == r) {
                return r;
            }
            int mid = (l + r) >> 1;
            int res;
            if (pred(surf + info[p << 1 | 1])) {
                res = findSurfixLast(p << 1 | 1, mid + 1, r, L, R, pred, surf);
            } else {
                surf = surf + info[p << 1 | 1];
                res = findSurfixLast(p << 1, l, mid, L, R, pred, surf);
            }
            return res;
        }
        int mid = (l + r) >> 1;
        int res = mid;
        if (mid + 1 <= R) {
            res = findSurfixLast(p << 1 | 1, mid + 1, r, L, R, pred, surf);
        }
        if (L <= mid and res == mid) {
            res = findSurfixLast(p << 1, l, mid, L, R, pred, surf);
        }
        return res;
    }
    template<class F>
    int findSurfixLast(int l, int r, const F& pred) {
        Info surf = Info();
        int res = findSurfixLast(1, 1, n, l, r, pred, surf);
        return res == l - 1 ? -1 : res;
    }
};

constexpr i64 inf = 2E13;
struct Info {
    i64 min = inf, max = 0;
    constexpr friend Info operator+(const Info& a, const Info& b) {
        return {std::min(a.min, b.min), std::max(a.max, b.max)};
    }
};

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int>a(n + 1);
    for (int i = 1; i <= n; i += 1) {
        std::cin >> a[i];
    }

    if (n == 1) {
        std::cout << 0 << '\n';
        return 0;
    }

    i64 res = inf;
    SegmentTree<Info>seg(n);
    for (int i = 1; i <= n; i += 1) {
        seg.modify(i, {a[i], a[i]});
    }

    // auto [x, y] = seg.info[1];
    // res = y - x;

    int top = 0;
    std::vector<int>stk(n + 1), ls(n + 1), rs(n + 1);
    for (int i = 1; i <= n; i += 1) {
        int k = top;
        while (k > 0 && a[i] > a[stk[k]]) {
            k -= 1;
        }
        if (k > 0) {
            rs[stk[k]] = i;
        }
        if (k < top) {
            ls[i] = stk[k + 1];
        }
        stk[top = (k += 1)] = i;
    }

    auto dfs = [&](auto && dfs, int p, int l, int r) ->void {
        if (p == 0) {
            return ;
        }
        dfs(dfs, ls[p], l, p - 1);
        dfs(dfs, rs[p], p + 1, r);
        auto x = seg.rangeQuery(1, l - 1), y = seg.rangeQuery(r + 1, n);
        i64 max = 0, min = inf;
        chmax(max, std::max(x.max, y.max));
        chmin(min, std::min(x.min, y.min));
        x = seg.rangeQuery(l, r);
        auto [u, v] = x;
        u *= 2;
        v *= 2;
        chmax(max, v);
        chmin(min, u);
        chmin(res, max - min);
    };
    dfs(dfs, stk[1], 1, n);

    std::cout << res << '\n';
    return 0;
}