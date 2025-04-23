template <class Info>
struct SparseTable {
	std::vector<std::vector<Info>>jump;

	SparseTable() = default;
	constexpr SparseTable(const auto& a) {
		int n = a.size() - 1;
		int logn = std::__lg(n);
		jump.assign(logn + 2, vector<Info>(n + 1, Info()));
		for (int i = 0; i <= n; i += 1) {
			jump[0][i] = Info(a[i]);
		}
		for (int j = 1; j <= logn + 1; j += 1) {
			for (int i = 1; i + (1 << (j - 1)) - 1 <= n; i += 1) {
				jump[j][i] = jump[j - 1][i] + jump[j - 1][i + (1 << (j - 1))]; 
			}
		}
	}

	constexpr Info range(int l, int r) {
		int k = r - l + 1;
		k = std::__lg(k);
		return jump[k][l] + jump[k][r - (1 << k) + 1];
	}
};