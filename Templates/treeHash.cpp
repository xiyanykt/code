static const u64 r = std::chrono::steady_clock::now().time_since_epoch().count();

u64 salt(u64 x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
}

u64 f(u64 x) {
    return salt(x + r);
}