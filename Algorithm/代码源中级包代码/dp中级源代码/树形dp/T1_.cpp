#include <bits/stdc++.h>
using namespace std;

const int N=2010;
const int inf = 1<<29;

vector<int> son[N];

int n, q, dp[N][N], a[N], sz[N];

void dfs(int u) {

	/*
		for (int j = 0; j < son[u].size(); j++) {
			int v = son[u][j];
		}
	*/

	sz[u] = 0;
	static int tmp[N];
	for (auto v:son[u]) {
		dfs(v);
		for (int i = 0; i <= sz[u] + sz[v]; i++) {
			tmp[i] = -inf;
		}
		for (int i = 0; i <= sz[u]; i++) {
			for (int j = 0; j <= sz[v]; j++) {
				tmp[i + j] = max(tmp[i + j], dp[u][i] + dp[v][j]);
			}
		}
		for (int i = 0; i <= sz[u] + sz[v]; i++)
			dp[u][i] = tmp[i];
		sz[u] += sz[v];
	}
	// u
	sz[u] += 1;
	for (int i = sz[u]; i >= 1; i--)
		dp[u][i] = dp[u][i-1] + a[u];
	dp[u][0] = 0;
}

int main() {
	scanf("%d%d",&n, &q);
	for (int i = 2; i <= n; i++) {
		int f;
		scanf("%d", &f);
		son[f].push_back(i);
	}
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	dfs(1);
	for (int i = 0; i < q; i++) {
		int u, m;
		scanf("%d%d",&u, &m);
		printf("%d\n", dp[u][m]);
	}
}