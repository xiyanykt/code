constexpr u64 Mod = (1ll << 60) - 1;

constexpr u64 add(u64 a, u64 b) {
    return (static_cast<__uint128_t>(a) + b) % Mod;
}

constexpr u64 mul(u64 a, u64 b) {
    return (static_cast<__uint128_t>(a) * b) % Mod;
}

constexpr u64 power(u64 a, u64 b) {
    u64 res = 1;
    for (; b > 0; b >>= 1, a = mul(a, a)) {
        if (b & 1) {
            res = mul(res, a);
        }
    }
    return res;
}

constexpr u64 inv(u64 x) {
    return power(x, Mod - 2);
}

constexpr u64 div(u64 a, u64 b) {
    return mul(a, inv(b));
}