template <class T>
constexpr T power(T a, i64 b) {
    T r = 1;
    for (; b != 0; b >>= 1, a = a * a) {
        if (b & 1) {
            r = r * a;
        }
    }
    return r;
}

template <class T, T P>
class ModuloInteger {
    T x;
    static T Mod;
    using i64 = long long;
    using i128 = __int128;
    
    static constexpr int multiply(int a, int b, const int Mod) {
        return i64(a) * b % Mod;
    }
    static constexpr i64 multiply(i64 a, i64 b, const i64 Mod) {
        return static_cast<i128>(a) * b % Mod;
    }

    T norm(T x) const {
        return (x < 0 ? x + getMod() : (x >= getMod() ? x - getMod() : x));
    }
public:
    ModuloInteger() : x{} {}
    ModuloInteger(i64 x) : x{norm(x % getMod())} {}
    static constexpr T getMod() {
        return (P > 0 ? P : Mod);
    }

    static void setMod(T m) {
        Mod = m;
    }

    T val() const {
        return x;
    }
    explicit operator T() const {
        return x;
    }

    ModuloInteger operator-() const {
        return ModuloInteger(getMod() - x);
    }

    ModuloInteger inv() const {
        assert(this->val() != 0);
        return ModuloInteger(power(*this, getMod() - 2));
    }

    ModuloInteger &operator*=(ModuloInteger& rsh) & {
        x = multiply(x, rsh.val(), getMod());
        return *this;
    }

    ModuloInteger &operator+=(ModuloInteger rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }

    ModuloInteger &operator-=(ModuloInteger rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    
    ModuloInteger &operator/=(ModuloInteger rhs) & {
        x = multiply(x, rhs.inv().val(), getMod());
        return *this;
    }

    friend  ModuloInteger operator+(ModuloInteger lhs, ModuloInteger rhs) {
        return lhs += rhs;
    }

    friend  ModuloInteger operator-(ModuloInteger lhs, ModuloInteger rhs) {
        return lhs -= rhs;
    }

    friend  ModuloInteger operator*(ModuloInteger lhs, ModuloInteger rhs) {
        return lhs *= rhs;
    }

    friend  ModuloInteger operator/(ModuloInteger lhs, ModuloInteger rhs) {
        return lhs /= rhs;
    }

    constexpr friend bool operator==(ModuloInteger lsh, ModuloInteger rsh) {
        return lsh.val() == rsh.val();
    }

    constexpr friend bool operator!=(ModuloInteger lsh, ModuloInteger rsh) {
        return lsh.val() != rsh.val();
    }

    constexpr friend std::strong_ordering operator<=>(ModuloInteger lsh, ModuloInteger rsh) {
        return lsh.val() <=> rsh.val();
    }

    friend  std::istream &operator>>(std::istream &is, ModuloInteger &a) {
        i64 v;
        is >> v;
        a = ModuloInteger(v);
        return is;
    }

    friend  std::ostream &operator<<(std::ostream &os, const ModuloInteger &a) {
        return os << a.val();
    }
};

template <>
int ModuloInteger<int, 0>::Mod = 998244353;
template <>
long long ModuloInteger<long long, 0>::Mod = 4179340454199820289;

// constexpr i64 P = 4179340454199820289;
// using Z = ModuloInteger<i64, P>;
constexpr int P = 998244353;
using Z = ModuloInteger<int, P>;

template <class T>
struct Polynomial : public std::vector<T> {
    static std::vector<T> w;
    static constexpr auto P = T::getMod();

    static void initW(int r) {
        if (w.size() >= r) {
            return ;
        }
        w.assign(r, 0);
        w[r >> 1] = 1;
        //primitiveroot of Mod
        T s = ::power(T(3), (P - 1) / r);
        for (int i = r / 2 + 1; i < r; i += 1) {
            w[i] = w[i - 1] * s;
        }
        for (int i = r / 2 - 1; i > 0; i -= 1) {
            w[i] = w[i * 2];
        }
    }

    static void dft(Polynomial& a) {
        const int n = a.size();
        assert((n & (n - 1)) == 0);
        initW(n);
        for (int k = (n >> 1); k; (k >>= 1)) {
            for (int i = 0; i < n; i += (k << 1)) {
                for (int j = 0; j < k; j += 1) {
                    auto v = a[i + j + k];
                    a[i + j + k] = (a[i + j] - v) * w[j + k];
                    a[i + j] = a[i + j] + v;
                }
            }
        }
    }

    static void idft(Polynomial& a) {
        const int n = a.size();
        assert((n & (n - 1)) == 0);
        initW(n);
        for (int k = 1; k < n; k <<= 1) {
            for (int i = 0; i < n; i += (k << 1)) {
                for (int j = 0; j < k; j += 1) {
                    auto x = a[i + j], y = a[i + j + k] * w[j + k];
                    a[i + j] = x + y;
                    a[i + j + k] = x - y;
                }
            }
        }
        a *= P - (P - 1) / n;
        std::reverse(a.begin() + 1, a.end());
    }

public:
    using std::vector<T>::vector;
    constexpr Polynomial truncate(int k) const {
        auto p = *this;
        p.resize(k);
        return p;
    }

    constexpr friend Polynomial operator+(const Polynomial& a, const Polynomial& b) {
        Polynomial p(std::max(a.size(), b.size()));
        for (int i = 0; i < p.size(); i += 1) {
            if (i < a.size()) {
                p[i] = p[i] + a[i];
            }
            if (i < b.size()) {
                p[i] = p[i] + b[i];
            }
        }
        return p;
    }

    constexpr friend Polynomial operator-(const Polynomial& a, const Polynomial& b) {
        Polynomial p(std::max(a.size(), b.size()));
        for (int i = 0; i < p.size(); i += 1) {
            if (i < a.size()) {
                p[i] = p[i] + a[i];
            }
            if (i < b.size()) {
                p[i] = p[i] - b[i];
            }
        }
        return p;
    }

    constexpr friend Polynomial operator-(const Polynomial& a) {
        int n = a.size();
        Polynomial p(n);
        for (int i = 0; i < n; i += 1) {
            p[i] = -a[i];
        }
        return p;
    }

    constexpr friend Polynomial operator*(T a, Polynomial b) {
        for (int i = 0; i < (int)b.size(); i += 1) {
            b[i] = b[i] * a;
        }
        return b;
    }

    constexpr friend Polynomial operator*(Polynomial a, T b) {
        for (int i = 0; i < int(a.size()); i += 1) {
            a[i] = a[i] * b;
        }
        return a;
    }

    constexpr friend Polynomial operator/(Polynomial a, T b) {
        b = b.inv();
        for (int i = 0; i < int(a.size()); i += 1) {
            a[i] = a[i] * b;
        }
        return b;
    }

    constexpr Polynomial mulxk(int k) const {
        auto p = *this;
        p.insert(p.begin(), k, 0);
        return p;
    }

    constexpr Polynomial modxk(int k) const {
        return Polynomial(this->begin(), this->begin() + k);
    }

    constexpr Polynomial divxk(int k) const {
        if (this->size() <= k) {
            return Polynomial{};
        }
        return Polynomial(this->begin() + k, this->end());
    }

    constexpr T whenXis(T x) const {
        T res = T{};
        for (int i = int(this->size()) - 1; i >= 0; i -= 1) {
            res = res * x + this->at(i);
        }
        return res;
    }

    constexpr Polynomial &operator+=(Polynomial b) {
        return (*this) = (*this) + b;
    }
    constexpr Polynomial &operator-=(Polynomial b) {
        return (*this) = (*this) - b;
    }
    constexpr Polynomial &operator*=(Polynomial b) {
        return (*this) = (*this) * b;
    }
    constexpr Polynomial &operator*=(T b) {
        return (*this) = (*this) * b;
    }
    constexpr Polynomial &operator/=(T b) {
        return (*this) = (*this) / b;
    }

    constexpr friend Polynomial operator*(const Polynomial& a, const Polynomial& b) {
        if (a.size() == 0 || b.size() == 0) {
            return Polynomial{};
        }
        int n = a.size() + b.size() - 1;
        int s = 1 << std::__lg(2 * n - 1);
        if ((((P - 1) & (s - 1)) != 0) || std::min(a.size(), b.size()) < 128) {
            Polynomial p(n);
            for (int i = 0; i < a.size(); i += 1) {
                for (int j = 0; j < b.size(); j += 1) {
                    p[i + j] = p[i + j] + a[i] * b[j];
                }
            }
            return p;
        }
        auto f = a.truncate(s), g = b.truncate(s);
        dft(f), dft(g);
        for (int i = 0; i < s; i += 1) {
            f[i] = f[i] * g[i];
        }
        idft(f);
        return f.truncate(n);
    }

    constexpr Polynomial deriv() const {
        int n = this->size();
        if (n <= 1) {
            return Polynomial{};
        }
        Polynomial p(n - 1);
        for (int i = 1; i < n; i += 1) {
            p[i - 1] = i * this->at(i);
        }
        return p;
    }

    constexpr Polynomial integr() const {
        int n = this->size();
        Polynomial p(n + 1);
        std::vector<T> _inv(n + 1);
        _inv[1] = 1;
        for (int i = 2; i <= n; i += 1) {
            _inv[i] = _inv[P % i] * (P - P / i);
        }

        for (int i = 0; i < n; i += 1) {
            p[i + 1] = this->at(i) * _inv[i + 1];
        }
        return p;
    }

    // assert(this->at(0) != 0)
    constexpr Polynomial inv(int m = -1) const {
        const int n = this->size();
        if (m < 0) {
            m = n;
        }

        Polynomial p = Polynomial{this->at(0).inv()};
        p.reserve(4 * m);
        for (int k = 2; k / 2 < m; k <<= 1) {
            Polynomial q = Polynomial(this->begin(), this->begin() + std::min(n, k)).truncate(2 * k);
            p.resize(2 * k);
            dft(p), dft(q);
            for (int i = 0; i < 2 * k; i += 1) {
                p[i] = p[i] * (2 - p[i] * q[i]);
            }
            idft(p);
            p.resize(k);
        }
        return p.truncate(m);
    }

    constexpr Polynomial ln(int m = -1) const {
        const int n = this->size();
        if (m < 0) {
            m = n;
        }
        return (deriv() * inv(m)).integr().truncate(m);
    }

    constexpr Polynomial exp(int m = -1) const {
        const int n = this->size();
        if (m < 0) {
            m = n;
        }

        Polynomial p{1};
        int k = 1;
        while (k < m) {
            k <<= 1;
            p = (p * (Polynomial{1} - p.ln(k) + truncate(k))).truncate(k);
        }
        return p.truncate(m);
    }

    constexpr Polynomial sqrt(int m = -1) const {
        const int n = this->size();
        if (m < 0) {
            m = n;
        }
        Polynomial p{1};
        int k = 1;
        constexpr T inv2 = T(2).inv();
        while (k < m) {
            k <<= 1;
            p = (p + (truncate(k) * p.inv(k)).truncate(k)) * inv2;
        }
        return p.truncate(m);
    }

    constexpr Polynomial power(long long k, int m, long long k2 = -1) const {
        if (0 < k and k <= (1 << 10)) {
            Polynomial p = (*this);
            Polynomial ans{1};
            for (; k; k >>= 1) {
                if (k & 1) {
                    ans *= p;
                    if (static_cast<int>(ans.size()) > m) {
                        ans.truncate(m);
                    }
                }

                p *= p;
                if (static_cast<int>(p.size()) > m) {
                    p.truncate(m);
                }
            }
            return ans.truncate(m);
        }

        k2 = k2 < 0 ? k : k2;
        unsigned int i = 0;
        while (i < this->size() and this->at(i) == T{}) {
            i++;
        }
        if (i == this->size() or k * i >= m) {
            return Polynomial(m, T{});
        }
        T v = this->at(i);
        Polynomial f = divxk(i) / v;
        return (f.ln(m - i * k) * k).exp(m - i * k).mulxk(i * k) * ::power(v, k2);
    }
};
template <class T>
std::vector<T> Polynomial<T>::w;

using Poly = Polynomial<Z>;
