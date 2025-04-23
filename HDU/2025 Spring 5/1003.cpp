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

static struct FastInput {
    static constexpr int BUF_SIZE = 1 << 20;
    char buf[BUF_SIZE];
    size_t chars_read = 0;
    size_t buf_pos = 0;
    FILE *in = stdin;
    char cur = 0;
 
    inline char get_char() {
        if (buf_pos >= chars_read) {
            chars_read = fread(buf, 1, BUF_SIZE, in);
            buf_pos = 0;
            buf[0] = (chars_read == 0 ? -1 : buf[0]);
        }
        return cur = buf[buf_pos++];
    }
 
    inline void tie(int) {
        
    }
 
    inline explicit operator bool() {
        return cur != -1;
    }
 
    inline static bool is_blank(char c) {
        return c <= ' ';
    }
 
    inline bool skip_blanks() {
        while (is_blank(cur) && cur != -1) {
            get_char();
        }
        return cur != -1;
    }
 
    inline FastInput& operator>>(char& c) {
        skip_blanks();
        c = cur;
        return *this;
    }
 
    inline FastInput& operator>>(std::string& s) {
        if (skip_blanks()) {
            s.clear();
            do {
                s += cur;
            } while (!is_blank(get_char()));
        }
        return *this;
    }
 
    template <typename T>
    inline FastInput& read_integer(T& n) {
        // unsafe, doesn't check that characters are actually digits
        n = 0;
        if (skip_blanks()) {
            int sign = +1;
            if (cur == '-') {
                sign = -1;
                get_char();
            }
            do {
                n += n + (n << 3) + cur - '0';
            } while (!is_blank(get_char()));
            n *= sign;
        }
        return *this;
    }
 
    template <typename T>
    inline typename std::enable_if<std::is_integral<T>::value, FastInput&>::type operator>>(T& n) {
        return read_integer(n);
    }
 
#if !defined(_WIN32) || defined(_WIN64)
    inline FastInput& operator>>(__int128& n) {
        return read_integer(n);
    }
#endif
 
    template <typename T>
    inline typename std::enable_if<std::is_floating_point<T>::value, FastInput&>::type operator>>(T& n) {
        // not sure if really fast, for compatibility only
        n = 0;
        if (skip_blanks()) {
            std::string s;
            (*this) >> s;
            sscanf(s.c_str(), "%lf", &n);
        }
        return *this;
    }
} fast_input;
 
static struct FastOutput {
    static constexpr int BUF_SIZE = 1 << 20;
    char buf[BUF_SIZE];
    size_t buf_pos = 0;
    static constexpr int TMP_SIZE = 1 << 20;
    char tmp[TMP_SIZE];
    FILE *out = stdout;
 
    inline void put_char(char c) {
        buf[buf_pos++] = c;
        if (buf_pos == BUF_SIZE) {
            fwrite(buf, 1, buf_pos, out);
            buf_pos = 0;
        }
    }
 
    ~FastOutput() {
        fwrite(buf, 1, buf_pos, out);
    }
 
    inline FastOutput& operator<<(char c) {
        put_char(c);
        return *this;
    }
 
    inline FastOutput& operator<<(const char* s) {
        while (*s) {
            put_char(*s++);
        }
        return *this;
    }
 
    inline FastOutput& operator<<(const std::string& s) {
        for (int i = 0; i < (int) s.size(); i++) {
            put_char(s[i]);
        }
        return *this;
    }
 
    template <typename T>
    inline char* integer_to_string(T n) {
        // beware of TMP_SIZE
        char* p = tmp + TMP_SIZE - 1;
        if (n == 0) {
            *--p = '0';
        } else {
            bool is_negative = false;
            if (n < 0) {
                is_negative = true;
                n = -n;
            }
            while (n > 0) {
                *--p = (char) ('0' + n % 10);
                n /= 10;
            }
            if (is_negative) {
                *--p = '-';
            }
        }
        return p;
    }
 
    template <typename T>
    inline typename std::enable_if<std::is_integral<T>::value, char*>::type stringify(T n) {
        return integer_to_string(n);
    }
 
#if !defined(_WIN32) || defined(_WIN64)
    inline char* stringify(__int128 n) {
        return integer_to_string(n);
    }
#endif
 
    template <typename T>
    inline typename std::enable_if<std::is_floating_point<T>::value, char*>::type stringify(T n) {
        sprintf(tmp, "%.17f", n);
        return tmp;
    }
 
    template <typename T>
    inline FastOutput& operator<<(const T& n) {
        auto p = stringify(n);
        for (; *p != 0; p++) {
            put_char(*p);
        }
        return *this;
    }
} fast_output;

struct HLD {
    int n;
    std::vector<std::vector<int>>adj;
    std::vector<int>dfn, siz, par, son, top, dep, seq;
    int cur;

    HLD() {}
    HLD(int n) {
        this->n = n;
        adj.assign(n + 1, std::vector<int>());
        dfn.resize(n + 1), par.resize(n + 1);
        son.resize(n + 1), siz.resize(n + 1);
        dep.resize(n + 1), top.resize(n + 1);
        seq.resize(n + 1);
        cur = 0;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u) {
        siz[u] += 1;
        dep[u] = dep[par[u]] + 1;
        for (const auto & v : adj[u]) {
            if (v == par[u]) {
                continue;
            }
            par[v] = u;
            dfs(v);
            siz[u] += siz[v];
            if (siz[v] > siz[son[u]]) {
                son[u] = v;
            }
        }
    }
    void dfs(int u, int h) {
        dfn[u] = ++cur;
        seq[cur] = u;
        top[u] = h;
        if (son[u]) {
            dfs(son[u], h);
        }
        for (const auto & v : adj[u]) {
            if (v == son[u] or v == par[u]) {
                continue;
            }
            dfs(v, v);
        }
    }

    void work(int s = 1) {
        dfs(s);
        dfs(s, s);
    }

    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) {
                std::swap(u, v);
            }
            u = par[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }

    int lca(int u, int v, int root) {
        return lca(u, v) ^ lca(u, root) ^ lca(v, root);
    }

    int dist(int u, int v) {
        return (dep[u] + dep[v] - 2 * dep[lca(u, v)]);
    }

    int jump(int u, int k) {
        if (dep[u] <= k) {
            return -1;
        }
        int d = dep[u] - k;
        while (dep[top[u]] > d) {
            u = par[top[u]];
        }
        return seq[dfn[u] + d - dep[u]];
    }

    int left(int u) {
        return dfn[u];
    }

    int right(int u) {
        return dfn[u] + siz[u] - 1;
    }

    bool isAncestor(int u, int v) {
        return dfn[u] <= dfn[v] and dfn[v] < dfn[u] + siz[u];
    }
};

// template<class Info>
// struct SegmentTree {
//     int n;
//     std::vector<Info>info;

//     SegmentTree() = default;

//     SegmentTree(const int & n) {
//         this->n = n;
//         info.assign(4 << std::__lg(n), Info());
//     }

//     SegmentTree(const std::vector<Info>& a) {
//         int n = a.size() - 1;
//         this->n = n;
//         info.assign(4 << std::__lg(n), Info());
//         auto work = [&](auto && self, int p, int l, int r) {
//             if (l == r) {
//                 info[p] = Info(a[l]);
//                 return;
//             }
//             int mid = (l + r) >> 1;
//             self(self, p << 1, l, mid), self(self, p << 1 | 1, mid + 1, r);
//             info[p] = info[p << 1] + info[p << 1 | 1];
//         };
//         work(work, 1, 1, n);
//     }

//     void modify(int p, int l, int r, int L, int R, const Info& v) {
//         if (l > R or r < L) {
//             return;
//         }
//         if (L <= l and r <= R) {
//             info[p] = v;
//             return;
//         }
//         int mid = (l + r) >> 1;
//         modify(p << 1, l, mid, L, R, v), modify(p << 1 | 1, mid + 1, r, L, R, v);
//         info[p] = info[p << 1] + info[p << 1 | 1];
//     }
//     void modify(int p, const Info& v) {
//         modify(1, 1, n, p, p, v);
//     }

//     Info rangeQuery(int p, int l, int r, int L, int R) {
//         if (l > R or r < L) {
//             return Info();
//         }
//         if (L <= l and r <= R) {
//             return info[p];
//         }
//         int mid = (l + r) >> 1;
//         return rangeQuery(p << 1, l, mid, L, R) + rangeQuery(p << 1 | 1, mid + 1, r, L, R);
//     }
//     Info rangeQuery(int l, int r) {
//         return rangeQuery(1, 1, n, l, r);
//     }

//     template<class F>
//     int findFirst(int p, int l, int r, int L, int R, F pred) {
//         if (l > R or r < L or not pred(info[p])) {
//             return -1;
//         }
//         if (l == r) {
//             return l;
//         }
//         int mid = (l + r) >> 1;
//         int res = findFirst(p << 1, l, mid, L, R, pred);
//         return res == -1 ? findFirst(p << 1 | 1, mid + 1, r, L, R, pred) : res;
//     }
//     template<class F>
//     int findFirst(int l, int r, F pred) {
//         return findFirst(1, 1, n, l, r, pred);
//     }

//     template<class F>
//     int findLast(int p, int l, int r, int L, int R, F pred) {
//         if (l > R or r < L or not pred(info[p])) {
//             return -1;
//         }
//         if (l == r) {
//             return r;
//         }
//         int mid = (l + r) >> 1;
//         int res = findLast(p << 1 | 1, mid + 1, r, L, R, pred);
//         return res == -1 ? findLast(p << 1, l, mid, L, R, pred) : res;
//     }
//     template<class F>
//     int findLast(int l, int r, F pred) {
//         return findLast(1, 1, n, l, r, pred);
//     }

//     template<class F>
//     int findPrefixFirst(int p, int l, int r, int L, int R, const F& pred, Info& pref) {
//         if (l > R or r < L) {
//             return r + 1;
//         }
//         if (L <= l and r <= R) {
//             if (not pred(pref + info[p])) {
//                 pref = pref + info[p];
//                 return r + 1;
//             }
//             if (l == r) {
//                 return l;
//             }
//             int mid = (l + r) >> 1;
//             int res;
//             if (pred(pref + info[p << 1])) {
//                 res = findPrefixFirst(p << 1, l, mid, L, R, pred, pref);
//             } else {
//                 pref = pref + info[p << 1];
//                 res = findPrefixFirst(p << 1 | 1, mid + 1, r, L, R, pred, pref);
//             }
//             return res;
//         }
//         int mid = (l + r) >> 1;
//         int res = mid + 1;
//         if (L <= mid) {
//             res = findPrefixFirst(p << 1, l, mid, L, R, pred, pref);
//         }
//         if (res == mid + 1 and mid + 1 <= R) {
//             res = findPrefixFirst(p << 1 | 1, mid + 1, r, L, R, pred, pref);
//         }
//         return res;
//     }
//     template<class F>
//     int findPrefixFirst(int l, int r, const F& pred) {
//         Info pref = Info();
//         int res = findPrefixFirst(1, 1, n, l, r, pred, pref);
//         return res == r + 1 ? -1 : res;
//     }

//     template<class F>
//     int findSurfixLast(int p, int l, int r, int L, int R, const F& pred, Info& surf) {
//         if (l > R or r < L) {
//             return l - 1;
//         }
//         if (L <= l and r <= R) {
//             if (not pred(surf + info[p])) {
//                 surf = surf + info[p];
//                 return l - 1;
//             }
//             if (l == r) {
//                 return r;
//             }
//             int mid = (l + r) >> 1;
//             int res;
//             if (pred(surf + info[p << 1 | 1])) {
//                 res = findSurfixLast(p << 1 | 1, mid + 1, r, L, R, pred, surf);
//             } else {
//                 surf = surf + info[p << 1 | 1];
//                 res = findSurfixLast(p << 1, l, mid, L, R, pred, surf);
//             }
//             return res;
//         }
//         int mid = (l + r) >> 1;
//         int res = mid;
//         if (mid + 1 <= R) {
//             res = findSurfixLast(p << 1 | 1, mid + 1, r, L, R, pred, surf);
//         }
//         if (L <= mid and res == mid) {
//             res = findSurfixLast(p << 1, l, mid, L, R, pred, surf);
//         }
//         return res;
//     }
//     template<class F>
//     int findSurfixLast(int l, int r, const F& pred) {
//         Info surf = Info();
//         int res = findSurfixLast(1, 1, n, l, r, pred, surf);
//         return res == l - 1 ? -1 : res;
//     }
// };

template<class T, const int M>
struct Basis {
    int zero;
    int cnt;
    std::array<T, M>a;
    std::array<T, M>t;

    Basis() {
        a.fill(0);
        t.fill(-1);
        cnt = 0;
        zero = 0;
    }

    bool add(T x, T y = std::numeric_limits<T>::max()) {
        for (int j = M - 1; j >= 0; j -= 1) {
            if (x >> j & 1) {
                if (not a[j]) {
                    a[j] = x;
                    t[j] = y;
                    cnt += 1;
                    return true;
                } else if (t[j] < y) {
                    std::swap(t[j], y);
                    std::swap(a[j], x);
                }
                x ^= a[j];
            }
        }
        zero = 1;
        return false;
    }

    T min(T x = std::numeric_limits<T>::max(), T l = {0}) {
        for (int j = M - 1; j >= 0; j -= 1) {
            if (a[j] and t[j] >= l) {
                x = std::min(x, x ^ a[j]);
            }
        }
        return x;
    }

    T max(T x = {0}, T l = {0}) {
        for (int j = M - 1; j >= 0; j -= 1) {
            if (a[j] and t[j] >= l) {
                x = std::max(x, x ^ a[j]);
            }
        }
        return x;
    }

    bool have(T x, T y = {0}) {
        for (int j = M - 1; j >= 0; j -= 1) {
            if (x >> j & 1 and t[j] >= y) {
                x ^= a[j];
            }
        }
        return x == 0;
    }

    T select(T k, T y = {0}) {
        auto b = a;
        // k -= zero;
        if (k >= (1ull << cnt)) {
            return -1;
        }
        std::vector<T>d;
        for (int i = 0; i <= M - 1; i += 1) {
            for (int j = i - 1; j >= 0; j -= 1) {
                if (b[i] >> j & 1) {
                    b[i] ^= b[j];
                }
            }
            if (b[i])d.push_back(b[i]);
        }
        T res = {0};
        for (int i = 0; i < d.size(); i += 1) {
            if (k >> i & 1) {
                res ^= d[i];
            }
        }
        return res;
    }
};

using basis = Basis<int, 30>;
struct Info {
    basis b{};
    Info() {}
    friend Info operator+(Info a, const Info& b) {
        for (int k = 29; k >= 0; k -= 1) {
            a.b.add(b.b.a[k]);
        }
        return a;
    }
};

template <typename Info, int N> struct Segment_Tree_Bit {
    constexpr static int offset = 1 << (std::__lg(N + 1) + 1);
    Info f[2 << (std::__lg(N + 1) + 1)];

    void build(int n, Info init) {
        for (int i = 1; i <= n; i++)
            f[i + offset] = init;
        for (int i = offset - 1; i >= 1; i--)
            f[i] = f[i << 1] + f[i << 1 | 1];
    }

    void update(int u, int x) {
        for (int i = u + offset; i; i >>= 1)
            f[i].b.add(x);
    }

    Info query(int l, int r) {
        Info res = Info();
        for (int i = l + offset - 1, j = r + offset + 1; i ^ j ^ 1; i >>= 1, j >>= 1) {
            if (!(i & 1)) res = res + f[i ^ 1];
            if ( (j & 1)) res = res + f[j ^ 1];
        }
        return res;
    }
};

Segment_Tree_Bit<Info, 100010>seg;

void solve () {
    int n, q;
    fast_input >> n >> q;

    HLD hld(n);
    for (int i = 1; i <= n - 1; i += 1) {
        int u, v;
        fast_input >> u >> v;
        hld.addEdge(u, v);
    }
    hld.work();

    // SegmentTree<Info>seg(n);
    // SegmentTree<Info>seg(n + 1);
    seg.build(n, Info());
    for (int t = 1; t <= q; t += 1) {
        int o;
        fast_input >> o;

        if (o == 1) {
            int p, x;
            fast_input >> p >> x;
            seg.update(hld.dfn[p], x);
        } else {
            int u, k;
            fast_input >> u >> k;

            // auto v = seg.rangeQuery(hld.left(u), hld.right(u));
            // fast_output << v.b.select(k) << '\n';
            // auto v = seg.product(hld.left(u), hld.right(u) + 1);
            auto v = seg.query(hld.left(u), hld.right(u));
            fast_output << v.b.select(k) << '\n';
        }
    }
}

auto main() ->int {
    std::ios::sync_with_stdio(false);
    // std::cin.tie(nullptr);

    int t;
    fast_input >> t;
    while (t--) {
        solve();
    }
    return 0;
}