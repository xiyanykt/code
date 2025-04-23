template <class T>
struct Polynomial : std::vector<T> {
    using F = std::complex<T>;
    static std::vector<int>r;
    static std::vector<F>w[2];

    static void initR(int log) {
        if (r.size() == (1 << log)) {
            return ;
        }
        int n = 1 << log;
        r.assign(n, 0);
        for (int i = 1; i < n; i += 1) {
            r[i] = (r[i >> 1] >> 1) | ((i & 1) << (log - 1));
        }
        w[0].assign(n, F());
        w[1].assign(n, F());
        const T pi = std::numbers::pi_v<T>;
        for (int i = 0; i < n; i += 1) {
            auto th = pi * i / n;
            auto cth = std::cos(th);
            auto sth = std::sin(th);
            w[0][i] = F(cth, sth);
            w[1][i] = F(cth, -sth);
        }
    }

    static void fft(std::vector<F>& a, bool invert) {
        int n = a.size();
        initR(std::__lg(n));
        for (int i = 0; i < n; i += 1) {
            if (i < r[i]) {
                std::swap(a[i], a[r[i]]);
            }
        }
        for (int m = 1; m < n; m <<= 1) {
            const int d = n / m;
            for (int R = m << 1, j = 0; j < n; j += R) {
                for (int k = 0; k < m; k += 1) {
                    auto x = a[j + k];
                    auto y = w[invert][d * k] * a[j + m + k];
                    a[j + k] = x + y;
                    a[j + m + k] = x - y;
                }
            }
        }
    }
public:
    using std::vector<T>::vector;
    constexpr friend Polynomial operator*(const Polynomial& a, const Polynomial& b) {
        if (a.size() == 0 || b.size() == 0) {
            return Polynomial{};
        }
        int n = a.size() + b.size() - 1;
        int l = std::__lg(2 * n - 1);
        int s = 1 << l;
        if (std::min(a.size(), b.size()) < 128) {
            Polynomial p(n);
            for (int i = 0; i < a.size(); i += 1) {
                for (int j = 0; j < b.size(); j += 1) {
                    p[i + j] += a[i] * b[j];
                }
            }
            return p;
        }
        std::vector<F>p(s), q(s);
        for (int i = 0; i < a.size(); i += 1) {
            p[i] = F(a[i], 0);
        }
        for (int i = 0; i < b.size(); i += 1) {
            q[i] = F(b[i], 0);
        }
        fft(p, false), fft(q, false);
        for (int i = 0; i < s; i += 1) {
            p[i] *= q[i];
        }
        fft(p, true);
        Polynomial h(n);
        for (int i = 0; i < n; i += 1) {
            h[i] = p[i].real() / s;
        }
        return h;
    }
};
template <class T>
std::vector<std::complex<T>> Polynomial<T>::w[2]{};
template <class T>
std::vector<int> Polynomial<T>::r;

using Poly = Polynomial<f64>;