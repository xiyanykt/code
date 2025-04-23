#include<bits/stdc++.h>
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;

    std::vector<int>a(n);
    for (int i = 0; i < n; i += 1) {
    	std::cin >> a[i];
    }

    std::vector<int>rec(n + 1);
    for (int i = 0; i < n; i += 1) {
    	rec[a[i]] += 1;
    }

    std::vector<int>v;
    for (int x = 1; x <= n; x += 1) {
    	if (rec[x]) {
    		v.push_back(rec[x]);
    	}
    }

    int ans = 0;
    while (v.size() >= 2) {
    	std::sort(v.begin(),v.end());
    	ans += 1;
    	v.back() -= 1;
    	v[v.size() - 2] -= 1;
    	if (v[v.size() - 2] == 0) {
    		std::swap(v[v.size() - 2], v.back());
    		v.pop_back();
    	}
    	if (v.back() == 0) {
    		v.pop_back();
    	}
    }

    std::cout << ans << '\n';
    return 0;
}