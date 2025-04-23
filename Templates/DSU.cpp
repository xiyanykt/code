struct DSU {
	std::vector<int>par, siz;
	DSU() = default;
	
	DSU(int n): par(n + 1), siz(n + 1, 1) {
        std::iota(par.begin(), par.end(), 0);
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