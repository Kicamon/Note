#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 101000;
vector<int> e[N];

int dfn[N], low[N], idx, n, m, sz;
bool cut[N];

void dfs(int u, int f) {
	dfn[u] = low[u] = ++idx;
	int ch = 0;
	for (auto v : e[u]) {
		if (!dfn[v]) {
			dfs(v, u);
			ch++;
			low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u]) cut[u] = 1;
		} else if (v != f) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (u == 1 && ch <= 1) cut[u] = 0;
	sz += cut[u];
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
	printf("%d\n", sz);
	for (int i = 1; i <= n; i++) if (cut[i])
		printf("%d ", i);
	puts("");
}
