#include "algo\xoxo.hpp"
// #include "algo\fast_io.hpp"

auto solve() {
    i64 x;
    cin >> x;

    i64 r = 1;
    while (x > 3) {
        r += r;
        x /= 4;
    }

    cout << r << '\n';
}

auto main() -> int {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}