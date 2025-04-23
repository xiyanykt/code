#include<bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f64 = long double;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

#ifndef ONLINE_JUDGE
#include "algo/debug.hpp"
#else
#define debug(...) (void)13
#endif

template<class T>
constexpr bool chmax (T& x, T y) {
    if (y > x) {
        x = y;
        return true;
    }
    return false;
}

template<class T>
constexpr bool chmin (T& x, T y) {
    if (y < x) {
        x = y;
        return true;
    }
    return false;
}

std::istream &operator>>(std::istream &is, i128 &n) {
	std::string s;
	is >> s;
	n = 0;
	for (int i = (s[0] == '-'); i < s.size(); i += 1) {
		n = n * 10 + s[i] - '0';
	}
	if (s[0] == '-') {
		n *= -1;
	}
	return is;
}

std::ostream &operator<<(std::ostream &os, i128 n) {
	std::string s;
	if (n == 0) {
		return os << 0;
	}
	bool sign = false;
	if (n < 0) {
		sign = true;
		n = -n;
	}
	while (n > 0) {
		s += '0' + n % 10;
		n /= 10;
	}
	if (sign) {
		s += '-';
	}
	std::reverse(s.begin(), s.end());
	return os << s;
}

void solve () {
    i128 n, k;
    std::cin >> n >> k;

    i128 ans = 0;
    if (k % 2 == 0) {
        i128 cnt = k / 2;
        i128 cyc = 4 * cnt;

        i128 div = n / cyc, mod = n % cyc;
        {
            ans += cnt * (1 + div) * div / 2;
            ans += cnt * (1 + div) * div / 2;

            ans += cnt * (1 + div) * div / 2;
            ans += cnt * div * (div - 1) / 2;
            
            ans += cnt * (1 + div) * div / 2;
            ans += cnt * div * (div - 1) / 2;
            
            ans += cnt * div * (div - 1) / 2;
            ans += cnt * div * (div - 1) / 2; 
        }

        i128 x = mod / cnt, y = mod % cnt;
        if (x >= 1) {
            ans += cnt * div;
            ans += cnt * div;
            for (int t = 1; t <= x - 1; t += 1) {
                ans += cnt * (div + 1);
                ans += cnt * div;
            }
        }

        if (x == 0) {
            ans += y * div;
            ans += y * div;
        } else if (x == 1) {
            ans += y * div;
            ans += y * (div + 1);
        } else if (x == 2) {
            ans += y * div;
            ans += y * (div + 1);
        } else {
            ans += y * (div + 1);
            ans += y * (div + 1);
        }
    }

    std::cout << ans << '\n';
}

auto main() ->int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
// 0 0 0 0
// 0 0 0 0
// 0 0 0 0
// 0 0