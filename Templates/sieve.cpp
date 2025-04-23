constexpr int Kn = 1E7;
int minp[Kn + 1];
std::vector<int>primes;

void sieve(int n) {
    for (int x = 2; x <= n; x += 1) {
        if (minp[x] == 0) {
            minp[x] = x;
            primes.push_back(x);
        }
        for (const auto & p : primes) {
            if (p * x > n) {
                break;
            }
            minp[p * x] = p;
            if (p == minp[x]) {
                break;
            }
        }
    }
}