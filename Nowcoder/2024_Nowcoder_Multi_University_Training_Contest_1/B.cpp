#include <iostream>
#include <vector>

using namespace std;

int MOD;

// Function to compute power modulo MOD
long long powerMod(long long base, long long exp, int mod) {
	long long result = 1;
	while (exp > 0) {
		if (exp % 2 == 1) {
			result = (result * base) % mod;
		}
		base = (base * base) % mod;
		exp /= 2;
	}
	return result;
}

int countSequences(int n, int m, int q) {
	// Total number of possible sequences
	long long totalSequences = powerMod((1LL << m), n, MOD);

	// Calculate number of sequences where all AND results are 0
	long long allZeroAndSequences = powerMod((1LL << m) - 1, n, MOD);

	// Number of sequences where there exists a non-empty subsequence with AND result 1
	long long result = (totalSequences - allZeroAndSequences + MOD) % MOD;

	return result;
}

int main() {
	int n, m, q;
	cin >> n >> m >> q;

	MOD = q;

	int result = countSequences(n, m, q);
	cout << result << endl;

	return 0;
}
