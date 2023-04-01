#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 110;
int g[N][N], mat[N];
bool vis[N];
int n, m;

bool dfs(int u) {
	for (int v = 1; v <= n; v++) if (g[u][v] && !vis[v]) {
		vis[v] = true;
		if (!mat[v] || dfs(mat[v])) {
			mat[v] = u;
			return true;
		}
	}
	return false;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		g[i][i] = 1;
	}
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		g[u][v] = 1;
	}
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				g[i][j] |= g[i][k] & g[k][j];
	for (int i = 1; i <= n; i++)
		g[i][i] = 0;
	int ans = n;
	for (int i = 1; i <= n; i++) {
		memset(vis, 0, sizeof(vis));
		if (dfs(i)) ans--;
	}
	printf("%d\n", ans);
}