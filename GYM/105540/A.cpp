#include<bits/stdc++.h>
using namespace std;
using i64 = long long;

int main () {
	cin.tie(nullptr)->ios::sync_with_stdio(false);

	int n, m, k;
	cin >> n >> m >> k;

	vector<string>s(n);
	for (auto& c : s) {
		cin >> c;
		c = ' ' + c;
	}
	std::map<std::string, int>rec;
	for (int i = 0; i < n; i += 1) {
		for (int j = 1; j <= m; j += 1) {
			int r = ((j) * k);
			std::string t = "";
			// cout << (j - 1) * k  + 1 << ' ' << r << '\n';
			for (int l = (j - 1) * k + 1; l <= r; l += 1) {
				t += s[i][l];
			}
			// cout << t << '\n';
			rec[t] += 1;
		}
	}

	for (int i = 0; i < n; i += 1) {
		for (int j = 1; j <= m; j += 1) {
			int r = ((j) * k);
			std::string t = "";
			// cout << (j - 1) * k  + 1 << ' ' << r << '\n';
			for (int l = (j - 1) * k + 1; l <= r; l += 1) {
				t += s[i][l];
			}
			// cout << t << '\n';
			// rec[t] += 1;
			if (rec[t] == 1) {
				std::cout << i + 1 << ' ' << j << '\n';
				return 0;
			}
		}
	}
	// cout << rec["QwQ"] << '\n';
	// assert(false);

	return 0;
}

