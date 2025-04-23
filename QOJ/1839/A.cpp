#include<bits/stdc++.h>
using namespace std;
using i64 = long long;

struct DSU {
	std::vector<int>par, siz;

	DSU() {

	}

	DSU(int n) {
		par.resize(n + 1);
		std::iota(par.begin() + 1, par.end(), 1);
		siz.assign(n + 1, 1);
	}

	int find(int x) {
		while (x != par[x]) {
			x = par[x] = par[par[x]];
		}
		return x;
	}

	bool same(int x, int y) {
		return find(x) == find(y);
	}

	bool merge(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) {
			return false;
		}
		if (siz[x] < siz[y]) {
			std::swap(x, y);
		}
		siz[x] += siz[y];
		par[y] = x;
		return true;
	}

	int size(int x) {
		return siz[find(x)];
	}
};

void solve () {
	string s1, s2, s3;
	cin >> s1 >> s2 >> s3;

	int a = s1.length(), b = s2.length(), c = s3.length();

	if (a != b) {
		std::cout << "NO\n";
	} else if (a != c) {
		std::cout << "YES\n";
	} else {
		constexpr int Kn = 26;
		DSU dsu(Kn);
		for (int i = 0; i < a; i += 1) {
			dsu.merge(s1[i] - 'a', s2[i] - 'a');
		}
		for (int i = 0; i < a; i += 1) {
			if (!dsu.same(s1[i] - 'a', s3[i] - 'a')) {
				std::cout << "YES\n";
				return ;
			}
		}
		std::cout << "NO\n";
	}
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
