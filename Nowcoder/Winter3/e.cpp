#include <bits/stdc++.h>
using f64 = double;
using i64 = long long;

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
        sprintf(tmp, "%.13f", n);
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

auto main() -> int {
    std::ios::sync_with_stdio(false);
    // std::cin.tie(nullptr);
    // std::cout << std::fixed << std::setprecision(9);
    int n, k;
    fast_input >> n >> k;

    std::vector<std::pair<int, int>> x(n + 1);
    for (int i = 1; i <= n; i += 1) {
        fast_input >> x[i].first >> x[i].second;
    }
   
    std::sort(x.begin() + 1, x.end());
    std::vector<std::pair<f64, int>> d(n + 1);
    auto work = [&](f64 t) {
        i64 c = 0;

        for (int i = 1; i <= n; i += 1) {
            auto [p, v] = x[i];
            d[i] = {f64(p) + t * v, i * v};
        }

        int f = 0;
        Fenwick<int>fen(n + 1);
        std::sort(d.begin() + 1, d.end());
        for (int i = 1; i <= n; i += 1) {
            auto [p, x] = d[i];
            if (x >= 1) {
                c += fen.rangeQuery(x + 1, n + 1);
            } else {
                fen.add(-x, 1);
            }
        }
        return c >= k;
    };

    f64 lo = 0, hi = 1e9;
    for (int t = 0; t <= 65; t += 1) {
        f64 mid = (lo + hi) / 2;
        if (work(mid)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    if (work(hi)) {
        fast_output << "Yes\n";
        fast_output << hi << '\n';
    } else {
        fast_output << "No\n";
    }
    return 0;
}