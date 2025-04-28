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
        k -= zero;
        if (k >= 1ull << cnt) {
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

constexpr int inf = 1E9;
template<class T, int M>
struct Linearbasis {
    bool has_zero = false;
    int dimension{0};
    std::array<T, M>basis {};
    std::array<int, M>time {};

    Linearbasis() {
        basis.fill(0);
        time.fill(-1);
    }

    bool insert(T val, int t = inf) noexcept {
        while (val) {
            int log = std::__lg(val);
            if (!basis[log]) {
                basis[log] = val;
                time[log] = t;
                ++dimension;
                return true;
            }
            if (time[log] < t) {
                std::swap(time[log], t);
                std::swap(basis[log], val);
            }
            val ^= basis[log];
        }
        has_zero = true;
        return false;
    }

    T max(T x = {0}, int t = 0) const noexcept {
        for (int k = M - 1; k >= 0; k -= 1) {
            if (basis[k] && time[k] >= t) {
                x = std::max(x, x ^ basis[k]);
            }
        }
        return x;
    }

    T min(T y = std::numeric_limits<T>::max(), int t = 0) const noexcept{
        for (int k = M - 1; k >= 0; k -= 1) {
            if (basis[k] && time[k] >= t) {
                y = std::min(y, y ^ basis[k]);
            }
        }
        return y;
    }

    bool contains(T val, int t = 0) const noexcept {
        for (int k = M - 1; k >= 0; k -= 1) {
            if ((val >> k & 1) && time[k] >= t) {
                val ^= basis[k];
            }
        }
        return val == 0;
    }

    T select(T k, int t = 0) const noexcept {
        u64 total = (1ULL << dimension) + (has_zero ? 1 : 0);
        if (k >= total) {
            return T{-1};
        }
        if (has_zero) {
            if (k == 0) {
                return T{};
            }
            k -= 1;
        }

        std::vector<T>r;
        for (int k = 0; k < M; k += 1) {
            if (!basis[k]) {
                continue;
            }
            T v = basis[k];
            for (int i = 0; i < k; i += 1) {
                if ((v >> i & 1)) {
                    v ^= basis[i];
                }
            }
            r.push_back(v);
        }

        T res = 0;
        for (int i = 0; i < int(r.size()); i += 1) {
            if (k >> i & 1) {
                res ^= r[i];
            }
        }
        return res;
    }

    void merge(const Linearbasis<T, M>& other, int t = 0) {
        for (int k = M - 1; k >= 0; k -= 1) {
            if (other.time[k] >= t) {
                insert(other.basis[k]);
            }
        }
    }
};

using basis = Linearbasis<int, 30>;