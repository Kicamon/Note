#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 101000;
vector<int> e[N];

int dfn[N], low[N], sz[N], idx, n, m;
ll ans[N];

void dfs(int u, int f) {
	dfn[u] = low[u] = ++idx;
	sz[u] = 1;
	ans[u] = n - 1;
	int cut = n - 1;
	for (auto v : e[u]) {
		if (!dfn[v]) {
			dfs(v, u);
			sz[u] += sz[v];
			low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u]) {
				ans[u] += (ll)sz[v] * (n - sz[v]);
				cut -= sz[v];
			}
		} else if (v != f) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	ans[u] += (ll)cut * (n - cut);
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; i++)
		printf("%lld\n", ans[i]);
}
