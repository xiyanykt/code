#include "W:\v\algo\math\modint.hpp"

template <class Z>
struct Comb {
	vector<Z>_fac;
	vector<Z>_invfac;

	Comb() = default;

	Comb(const int & n) {
		_fac.resize(n + 1);
		_invfac.resize(n + 1);
		_fac[0] = _invfac[0] = 1;

		for (int i = 1; i <= n; i += 1) {
			_fac[i] = _fac[i - 1] * i;
		}
		_invfac[n] = _fac[n].inv();
		for (int i = n - 1; i >= 1; i -= 1) {
			_invfac[i] = _invfac[i + 1] * i;
		}
	}

	Z fac(int n) {
		return _fac[n];
	}

	Z invfac(int n) {
		return _invfac[n];
	}

	Z binom(int n, int m) {
		if (n < m || m < 0 || n < 0) {
			return Z(0);
		}
		return fac(n) * invfac(m) * invfac(n - m);
	}
};