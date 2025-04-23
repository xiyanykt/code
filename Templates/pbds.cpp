#include<bits/stdc++.h>

using i64 = long long;

#include<bits/extc++.h>
using namespace __gnu_pbds;

template<class KT, class VT = null_type>
using RBT = tree<KT, VT, std::less<KT>, rb_tree_tag, tree_order_statistics_node_update>;

// constexpr i64 inf = 3E18;
constexpr int inf = 1E9;

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	RBT<std::pair<int, int>>S;

	int Q;
	std::cin >> Q;

	int H = 1;

	while (Q--) {
		int op, x;
		std::cin >> op >> x;
		if (op == 1) {
			S.insert({x, H++});
		} else if (op == 2) {
			auto it = S.upper_bound({x, 0});
			S.erase(it);
		} else if (op == 3) {
			auto it = S.order_of_key({x, 0});
			std::cout << (it + 1) << "\n";
		} else if (op == 4) {
			auto it = S.find_by_order(x - 1);
			std::cout << (it->first) << "\n";
		} else if (op == 5) {
			auto it = S.lower_bound({x, 0});
			std::cout << (std::prev(it)->first) << "\n";
		} else if (op == 6) {
			auto it = S.upper_bound({x, inf});
			std::cout << (it->first) << "\n";
		}
	}

	return 0;
}