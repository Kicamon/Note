#include <bits/stdc++.h>
using namespace std;

const int N=1010, M = 10010;
const int inf = 1<<29;

vector<int> son[N];

int n, m, tot, l[N], r[N], id[N];
int dp[N][M], a[N], w[N];

void dfs(int u) {
	l[u] = ++tot;
	id[tot] = u;
	for (auto v : son[u]) {
		dfs(v);
	}
	r[u] = tot;
}

int main() {
	scanf("%d%d",&n, &m);
	for (int i = 2; i <= n; i++) {
		int f;
		scanf("%d", &f);
		son[f].push_back(i);
	}
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++)
		scanf("%d", &w[i]);
	dfs(1);
	for (int j = 1; j <= m; j++) dp[n + 1][j] = -inf;
	for (int i = n; i >= 1; i--) {
		int u = id[i];
		for (int j = 0; j <= m; j++) {
			dp[i][j] = dp[r[u] + 1][j];
			if (j >= w[u])
				dp[i][j] = max(dp[i][j], dp[i + 1][j - w[u]] + a[u]);
		}
	}
	for (int i = 0; i <= m; i++) {
		if (dp[1][i] >= 0) printf("%d\n", dp[1][i]);
		else printf("0\n");
	}
}