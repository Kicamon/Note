#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=2010;
const ll inf = 1ll<<60;


int n, m, f[N], dep[N];

vector<int> son[N];
vector<array<int, 2>> path[N];

ll dp[N][N];

void merge(ll *a, ll *b, int len) {
	static ll sufa[N], sufb[N];
	// for (i = 1;i<=len; i++) for (int j=1; j<=len; j++)
	//  a[i] + b[j] -> tmp[min(i, j)];
	sufa[len + 1] = inf;
	sufb[len + 1] = inf;
	for (int i = len; i >= 1; i--) {
		sufa[i] = min(sufa[i + 1], a[i]);
		sufb[i] = min(sufb[i + 1], b[i]);
	}
	for (int i = 1; i <= len; i++) {
		a[i] = min(a[i] + sufb[i], b[i] + sufa[i]);
	}
}

void dfs(int u) {
	for (int i = 1; i <= dep[u]; i++) dp[u][i] = inf;
	for (auto p: path[u]) {
		dp[u][dep[p[0]]] = min(dp[u][dep[p[0]]], (ll)p[1]);
	}
	// dp[u][dep[u] + 1] = 0
	for (auto v : son[u]) {
		dfs(v);
		merge(dp[u], dp[v], dep[v]);
		/*
		for (i = 1; i <= n; i++)
			for (int j = 1; j <= dep[v]; j++)
				tmp[min(i, j)] = min(dp[u][i] + dp[v][j], tmp[min(i, j)]);
		*/
	}
}

int main() {
	scanf("%d%d", &n, &m);
	dep[1] = 1;
	for (int i = 2; i <= n; i++) {
		scanf("%d", &f[i]);
		son[f[i]].push_back(i);
		dep[i] = dep[f[i]] + 1;
	}
	for (int i = 1; i <= m; i++) {
		int u, v, a;
		scanf("%d%d%d", &u, &v, &a);
		path[v].push_back({u, a});
	}
	dfs(1);
	if (dp[1][1] >= inf) puts("-1");
	else printf("%lld\n", dp[1][1]);
}
