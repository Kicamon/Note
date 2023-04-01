#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 101000;
vector<pair<int, int>> e[N];

int dfn[N], low[N], idx, n, m, cnt;
int bel[N];
int fe[N], par[N], f[N], dep[N];
stack<int> stk;
array<int, 2> E[N];
char ans[N];

int find(int x) {
	return f[x] == x ? x : f[x] = find(f[x]);
}

void dfs(int u, int id) {
	dfn[u] = low[u] = ++idx;
	stk.push(u);
	for (auto [v, id2] : e[u]) {
		if (!dfn[v]) {
			dfs(v, id2);
			low[u] = min(low[u], low[v]);
		} else if (id != id2) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (dfn[u] == low[u]) {
		++cnt;
		fe[cnt] = id;
		while (true) {
			int w = stk.top();
			bel[w] = cnt;
			stk.pop();
			if (w == u) break;
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back({v, i});
		e[v].push_back({u, i});
		E[i] = {u, v};
		ans[i] = 'B';
	}
	for (int i = 1; i <= n; i++) if (!dfn[i])
		dfs(i, -1);
	for (int i = 1; i <= cnt; i++) {
		if (fe[i] == -1) par[i] = 0;
		else {
			int u = E[fe[i]][0], v = E[fe[i]][1];
			if (bel[u] != i) par[i] = bel[u]; else par[i] = bel[v];
		}
	}
	for (int i = cnt; i >= 1; i--) {
		f[i] = i;
		dep[i] = dep[par[i]] + 1;
	}
	int p;
	scanf("%d", &p);
	for (int i = 1; i <= p; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		u = find(bel[u]); v = find(bel[v]);
		while (u != v) {
			if (dep[u] > dep[v]) {
				ans[fe[u]] = (bel[E[fe[u]][0]] == u)? 'R' : 'L';
				f[u] = par[u];
				u = find(par[u]);
			} else {
				ans[fe[v]] = (bel[E[fe[v]][0]] == v)? 'L' : 'R';
				f[v] = par[v];
				v = find(par[v]);
			}
		}
	}
	puts(ans);
}
