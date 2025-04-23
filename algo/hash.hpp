struct customHash {
    static unsigned long long salt(unsigned long long x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(unsigned long long x) const {
        static const unsigned long long r = std::chrono::steady_clock::now().time_since_epoch().count();
        return salt(x + r);
    }
};
