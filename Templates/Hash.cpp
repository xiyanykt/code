std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

u64 rand(i64 l, i64 r) {
    return std::uniform_int_distribution<u64>(l, r)(rng);
}

static constexpr u64 Mod = (1ull << 61) - 1;

static constexpr u64 add(u64 a, u64 b) {
    u64 c = a + b;
    if (c >= Mod) {
        c -= Mod;
    }
    return c;
}

static constexpr u64 mul(u64 a, u64 b) {
    __uint128_t c = static_cast<__uint128_t>(a) * b;
    return add(c >> 61, c & Mod);
}

std::vector<u64>pw{1};
u64 htt = rand(Mod / 3, Mod / 2);

struct Hash : public std::vector<u64> {
    Hash() = default;
    Hash(const std::string& s) {
        int n = s.size();
        this->resize(n + 1);
        while (int(pw.size()) <= n) {
            pw.push_back(mul(pw.back(), htt));
        }
        for (int i = 1; i <= n; i += 1) {
            this->at(i) = add(mul(this->at(i - 1), htt), int(s[i - 1]));
        }
    }

    constexpr u64 rangeQuery(int l, int r) const {
        return add(this->at(r), Mod - mul(this->at(l - 1), pw[r - l + 1]));
    }
};