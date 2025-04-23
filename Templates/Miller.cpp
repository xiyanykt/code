std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int64_t rand(int64_t l, int64_t r) {
    return std::uniform_int_distribution<int64_t>(l, r)(rng);
}

int64_t mul(int64_t x, int64_t y, int64_t mod) {
    return static_cast<__int128_t>(x) * y % mod;
}

int64_t power(int64_t a, int64_t n, int64_t mod) {
    int64_t res = 1;
    for (; n != 0; n >>= 1, a = mul(a, a, mod)) {
        if (n % 2 == 1) {
            res = mul(res, a, mod);
        }
    }
    return res;
}

bool isPrime(int64_t n) {
    if (n == 2 or n == 3) {
        return true;
    }
    if (n <= 1 or n % 2 == 0) {
        return false;
    }
    static constexpr int64_t A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    int64_t u = n - 1, k = 0;
    while (u % 2 == 0) {
        u >>= 1;
        k += 1;
    }
    for (const auto & x : A) {
        if (x % n == 0) {
            continue;
        }
        int64_t v = power(x, u, n);
        if (v == 1 or v == n - 1) {
            continue;
        }
        for (int j = 1; j <= k; j += 1) {
            int64_t last = v;
            v = mul(v, v, n);
            if (v == 1) {
                if (last != n - 1) {
                    return false;
                }
                break;
            }
        }
        if (v != 1) {
            return false;
        }
    }
    return true;
}

int64_t Pollardsrho(i64 n) {
    int64_t c = rand(1, n - 1);
    int64_t x = 0, y = 0, s = 1;
    for (int k = 1;; k <<= 1, y = x, s = 1) {
        for (int i = 1; i <= k; i += 1) {
            x = (static_cast<__int128_t>(x) * x + c) % n;
            s = mul(s, std::abs(x - y), n);
            if (i % 127 == 0) {
                int64_t d = std::gcd(s, n);
                if (d > 1) {
                    return d;
                }
            }
        }
        int64_t d = std::gcd(s, n);
        if (d > 1) {
            return d;
        }
    }
    return n;
}

std::vector<int64_t> factorize(int64_t n) {
    std::vector<int64_t>res;
    auto f = [&](auto && f, int64_t n) ->void {
        if (n <= 1) {
            return ;
        }
        if (isPrime(n)) {
            res.push_back(n);
            return ;
        }
        int64_t x = n;
        while (x == n) {
            x = Pollardsrho(x);
        }
        assert(x != 0);
        f(f, x);
        f(f, n / x);
    };
    f(f, n);
    std::sort(res.begin(), res.end());
    return res;
}

std::vector<int64_t> divisors(int64_t n) {
    const auto facp = factorize(n);
    std::vector<std::pair<int64_t, int>>pf;
    for (const auto & c : facp) {
        if (pf.empty() or c != pf.back().first) {
            pf.push_back({c, 1});
        } else {
            pf.back().second += 1;
        }
    }
    std::vector<int64_t> d;
    auto f = [&](auto && f, int u, int64_t pw) ->void {
        if (u >= std::ssize(pf)) {
            d.push_back(pw);
            return ;
        }
        for (int i = 0; i <= pf[u].second; i += 1) {
            f(f, u + 1, pw);
            pw *= pf[u].first;
        }
    };
    f(f, 0, 1);
    return d;
}