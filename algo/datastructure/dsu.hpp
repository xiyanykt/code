struct DSU {
	vector<int>par, siz;

	DSU() {

	}
	
	DSU(int n) {
		par.resize(n + 1);
		iota(par.begin() + 1, par.end(), 1);
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
			swap(x, y);
		}
		siz[x] += siz[y];
		par[y] = x;
		return true;
	}

	int size(int x) {
		return siz[find(x)];
	}
};

struct RevocableDSU {
	vector<int>par, siz;
	vector<pair<int&, int>>rolp, rols;

	RevocableDSU() = default;

	RevocableDSU(const int & n) {
		par.resize(n + 1);
		iota(par.begin(), par.end(), 0);
		siz.assign(n + 1, 1);
		rolp.clear();
		rols.clear();
	}

	int find(int x) {
		while (x != par[x]) {
			x = par[x];
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
			swap(x, y);
		}
		rolp.emplace_back(par[y], par[y]);
		rols.emplace_back(siz[x], siz[x]);
		par[y] = x;
		siz[x] += siz[y];
		return true;
	}

	int size(int u) {
		return siz[find(u)];
	}

	int version() {
		return rolp.size();
	}

	void rollback(int v) {
		while (rolp.size() > v) {
			rolp.back().first = rolp.back().second;
			rols.back().first = rols.back().second;
			rolp.pop_back();
			rols.pop_back();
		}
	}
};