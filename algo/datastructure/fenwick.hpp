template<class T>
struct Fenwick {
	int n;
	vector<T>a;

	Fenwick() {

	}

	Fenwick(const int& n) {
		this->n = n;
		a.assign(n + 1, T{});
	}

	void add(int p, const T& x) {
		if (p >= 1 && p <= n) {
			while (p <= n) {
				a[p] += x;
				p += p & -p;
			}
		}
	}

	T sum(int p) {
		T res {};
		if (p >= 1 && p <= n) {
			while (p >= 1) {
				res += a[p];
				p -= p & -p;
			}
		}
		return res;
	}

	T range(int l, int r) {
		return sum(r) - sum(l - 1);
	}

	int select(int k) {
		int x = 0;
		T cur = T();
		for (int k = __lg(n); ~k; k -= 1) {
			x += 1 << k;
			if (x >= n || cur + a[x] >= k) {
				x -= 1 << k;
			} else {
				cur = cur + a[x];
			}
		}
		return x + 1;
	}
};