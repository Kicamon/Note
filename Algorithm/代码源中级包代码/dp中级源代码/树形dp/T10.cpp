#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;
const int N = 110;

int n, k, g[N][N];
int cnt[N], dp[N];

void solve() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			g[i][j] = (i == j)? 0 : mod; 
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		g[u][v] = g[v][u] = 1;
	}
	if (k == 2) {
		printf("%d\n", n * (n - 1) / 2);
		return;
	}
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int d = 1; d <= n; d++) {
			for (int j = 1; j <= n; j++) cnt[j] = 0;
			for (int u = 1; u <= n; u++) if (g[i][u] == d) {
				for (int v = 1; v <= n; v++) if (g[i][v] == 1 && g[i][u] == g[i][v] + g[v][u]) {
					cnt[v]++;
				}
			}
			for (int j = 1; j <= k; j++) dp[j] = 0;
			dp[0] = 1;
			for (int j = 1; j <= n; j++) if (cnt[j] > 0) {
				for (int l = k; l >= 1; l--) dp[l] = (dp[l] + 1ll * dp[l - 1] * cnt[j]) % mod;
			}
			ans = (ans + dp[k]) % mod;
		}
	}
	printf("%d\n", ans);
}

int main() {
	int tc;
	scanf("%d",&tc);
	for (int i = 1; i <= tc; i++) {
		solve();
	}
}