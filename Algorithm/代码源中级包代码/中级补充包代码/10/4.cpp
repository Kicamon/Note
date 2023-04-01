#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 50010;
const int B = 200;
int n, k;
int a[N][5], pos[5][N];
bitset<N> f[5][N / B + 10], s, ans;

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < k; j++) {
			scanf("%d", &a[i][j]);
			pos[j][a[i][j]] = i;
		}
	}
	for (int j = 0; j < k; j++) {
		for (int c = B; c <= n; c += B)	{
			int t = c / B;
			f[j][t] = f[j][t - 1];
			for (int i = c - B + 1; i <= c; i++)
				f[j][t][pos[j][i]] = 1;
		}
	}
	for (int i = 1; i <= n; i++) {
		ans.set();
		for (int j = 0; j < k; j++) {
			// <= a[i][j]
			s = f[j][a[i][j] / B];
			for (int l = a[i][j] / B * B + 1; l <= a[i][j]; l++)
				s[pos[j][l]] = 1;
			ans &= s;
		}
		printf("%d\n", (int)ans.count() - 1);
	}
}