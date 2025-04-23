#include<bits/stdc++.h>
using namespace std;
using i64 = long long;

constexpr int Kn = 1E5;
template<typename T>
struct Fenwick {
	int n;
	std::vector<T>a;

	Fenwick() {}
	Fenwick(int n) {
		this->n = n;
		a.assign(n + 1, T());
	}

	void add(int p, const T& x) {
		for (int i = p; i <= n; i += i & -i) {
			a[i] += x;
		}
	}

	T sum(int p) {
		T ans = T();
		for (int i = p; i > 0; i -= i & -i) {
			ans += a[i];
		}
		return ans;
	}

	T getRange(int l, int r) {
		return sum(r) - sum(l - 1);
	}

	int select(int k) {
		int x = 0;
		T cur = T();
		for (int i = std::__lg(n); ~i; i -= 1) {
			x += 1 << i;
			if (x >= n or cur + a[x] >= k) {
				x -= 1 << i;
			} else {
				cur = cur + a[x];
			}
		}
		return x + 1;
	}
};

void solve () {
	int n;
	cin >> n;

	vector<int>x(n + 1), y(n + 1), z(n + 1);
	for (int i = 1; i <= n; i += 1) {
		std::cin >> x[i] >> y[i] >> z[i];
	}

	std::map<int, int>cx, cy, cz;
	for (int i = 1; i <= n; i += 1) {
		cx[x[i]] += 1;
		cy[y[i]] += 1;
		cz[z[i]] += 1;
	}

	Fenwick<int>fen(n);
	std::vector<int>p(n + 1);
	for (int i = 1; i <= n; i += 1) {
		p[i] = max(p[i], cx[x[i]]);
		p[i] = max(p[i], cy[y[i]]);
		p[i] = max(p[i], cz[z[i]]);
		fen.add(p[i], 1);
	}

	std::cout << 0 << ' ';	
	for (int k = 1; k <= n - 1; k += 1) {
		std::cout << fen.sum(k) << ' ';
	}
	std::cout << '\n';
}

int main () {
	cin.tie(nullptr)->ios::sync_with_stdio(false);

	int t = 1;
	cin >> t;

	while (t --) {
		solve();
	}
	return 0;
}
