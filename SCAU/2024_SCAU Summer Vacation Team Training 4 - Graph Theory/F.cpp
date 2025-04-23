#include<bits/stdc++.h>
using namespace std;
const int N = 1009;
bitset<N>b[N];
int main() {
	int n, m, i, j;
	for (scanf("%d%d", &n, &m); m--;)scanf("%d%d", &i, &j), b[i][j] = 1;
	for (i = 1; i <= n; ++i)for (j = 1; j <= n; ++j)if (b[j][i])b[j] |= b[i];
	for (j = n * (n - 1) / 2, i = 1; i <= n; ++i)j -= b[i].count();
	printf("%d", j);
	return 0;
}
