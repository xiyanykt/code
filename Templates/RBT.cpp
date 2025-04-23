#include<bits/stdc++.h>

using i64 = int64_t;

// #include<bits/extc++.h>
#include<ext/pb_ds/assoc_container.hpp>
// #include<ext/pb_ds/tree_policy.hpp>
// #include<ext/pb_ds/hash_policy.hpp>
// #include<ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;

template<class KT, class VT = null_type>
using RBT = tree<KT, VT, std::less<KT>, rb_tree_tag, tree_order_statistics_node_update>;

constexpr i64 inf = 2E18;

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int q;
	i64 k;
	std::cin >> q >> k;

	RBT<i64>s, p;

	s.insert(inf), s.insert(-inf), p.insert(inf), p.insert(-inf);
	while (q--) {
		int op;
		i64 x;
		std::cin >> op >> x;
		if (op == 1) {
			auto it = s.find(x);
			if (it == s.end()) {
				auto w = s.insert(x).first;
				auto u = *std::prev(w), v = *std::next(w);
				p.erase(u);
				if (v - x > k) {
					p.insert(x);
				}
				if (x - u > k) {
					p.insert(u);
				}
			} else {
				p.erase(x);
				auto u = *std::prev(it), v = *std::next(it);
				if (v - u > k) {
					p.insert(u);
				}
				s.erase(it);
			}
		} else {
			auto u = p.lower_bound(x);
			auto v = std::prev(u);
			std::cout << s.order_of_key(*u) - s.order_of_key(*v) << "\n";
		}
	}
	return 0;
}