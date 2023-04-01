#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 210;

int n, m, mod;
ll g[N][N];

int calc(int n) {
	ll ans = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			g[i][j] %= mod;
	for (int i = 1; i <= n; i++) {
		/*
		if (g[i][i] == 0) {
			找一个 j 不等于g[j][i] != 0，交换，答案 * (-1)
		}
		for (int j = i + 1; j <= n; j++) {
			double t = g[j][i] / g[i][i];
			for (int k = i ... n)
				g[j][k] -= t * g[i][k];
		}
		*/
		for (int j = i + 1; j <= n; j++) {
			// 消掉 g[j][i]
			int x = i, y = j;
			while (g[x][i]) {
				int t = g[y][i] / g[x][i];
				for (int k = i; k <= n; k++)
					g[y][k] = (g[y][k] - t * g[x][k]) % mod;
				swap(x, y);
			}
			// g[x][i] = 0
			if (x == i) {
				for (int k = i; k <= n; k++)
					swap(g[i][k], g[j][k]);
				ans = -ans;
			}
		}
		if (g[i][i] == 0) {
			return 0;
		}
		ans = ans * g[i][i] % mod;
	}
	if (ans < 0) ans += mod;
	return ans;
}

int main() {
	scanf("%d%d%d", &n, &m, &mod);
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		g[u][v]--;
		g[v][u]--;
		g[u][u]++;
		g[v][v]++;
	}
	printf("%d\n", calc(n - 1));
}
