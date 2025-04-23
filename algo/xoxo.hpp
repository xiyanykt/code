#include<bits/stdc++.h>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f64 = long double;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

using namespace std;

template<class T>
constexpr bool chmax(T& x, T y) {
    if (y > x) {
        x = y;
        return true;
    }
    return false;
}

template<class T>
constexpr bool chmin(T& x, T y) {
    if (y < x) {
        x = y;
        return true;
    }
    return false;
}

#ifndef ONLINE_JUDGE
template<class T, size_t size = tuple_size<T>::value>
string to_debug(T, string s = "")
requires(not ranges::range<T>);

string to_debug(auto x)
requires requires(ostream &os) {
    os << x;
}{
    return static_cast<ostringstream>(ostringstream() << x).str();
}

string to_debug(ranges::range auto x, string s = "")
requires(not is_same_v<decltype(x), string>) {
    for (auto xi : x) {
        s += ", " + to_debug(xi);
    }
    return "[" + s.substr(s.empty() ? 0 : 2) + "]";
}

template<class T, size_t size>
string to_debug(T x, string s)
requires(not ranges::range<T>) {
    [&]<size_t... I>(index_sequence<I...>) {
        ((s += ", " + to_debug(get<I>(x))), ...);
    }(make_index_sequence<size>());
    return "(" + s.substr(s.empty() ? 0 : 2) + ")";
}

#define debug(...) cerr << "(" #__VA_ARGS__ ") = " << to_debug(tuple(__VA_ARGS__)) << "\n"
#else
#define debug(...) (void)13
#endif