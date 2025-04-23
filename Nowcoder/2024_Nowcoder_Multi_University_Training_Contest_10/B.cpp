#include<bits/stdc++.h>

#pragma GCC optimize("O2")
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
#pragma GCC target("sse4,popcnt,abm,mmx")

using i64 = int64_t;
using u64 = uint64_t;
using f64 = long double;

#ifndef ONLINE_JUDGE
#include "algo\debug.hpp"
#else
#define debug(...) (void)42
#endif

template<class T>
void chmax(T& x, T y) {
	x = std::max(x, y);
}

template<class T>
void chmin(T& x, T y) {
	x = std::min(x, y);
}

constexpr int N = 1 << 20;
struct Node {
	Node *lsh = nullptr, *rsh = nullptr;
	int left = 0, right = 0;
} pool[N << 3];

int tot = 0;

Node* find(const std::string& s, int l, int r) {
	Node* ptr = &pool[tot++];
	ptr->left = l, ptr->right = r;
	int j = -1;
	for (int i = l, pref = 0; i <= r; i += 1) {
		if (s[i] == '<') {
			pref += 1;
		}
		if (s[i] == '>') {
			pref -= 1;
		}
		if (s[i] == ',' and pref == 1) {
			j = i;
			break;
		}
	}
	if (j != -1) {
		ptr->lsh = find(s, l + 5, j - 1);
		ptr->rsh = find(s, j + 1, r - 1);
	}
	return ptr;
}

void dfs(Node* ptr) {
	if (ptr == nullptr) {
		return ;
	}
	std::cout << ptr->left << " " << ptr->right << "\n";
	dfs(ptr->lsh);
	dfs(ptr->rsh);
}

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, q;
	std::cin >> n >> q;

	std::map<std::string, std::string>rel;
	std::map<std::string, Node *>rec;
	for (int i = 1; i <= n; i += 1) {
		std::string type, var;
		std::cin >> type >> var;
		int m = type.size();

		var.pop_back();
		rec[var] = find(type, 0, m - 1);
		rel[var] = type;

		// std::cout << type << "\n";
		// dfs(rec[var]);
		// std::cout << "\n";
	}

	while (q--) {
		std::string s;
		std::cin >> s;
		if (s.find('.') == s.npos) {
			std::cout << rel[s] << "\n";
		} else {
			int j = s.find('.');
			std::string var = s.substr(0, j);
			Node* cur = rec[var];
			while (j != s.npos) {
				if (s[j + 1] == 'f') {
					cur = cur->lsh;
				} else {
					cur = cur->rsh;
				}
				j = s.find('.', j + 1);
			}
			const auto Y = rel[var];
			for (int i = cur->left; i <= cur->right; i += 1) {
				std::cout << Y[i];
			}
			std::cout << "\n";
		}
	}
	return 0;
}
