#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 101000;
const int inf = 1 << 30;

vector<int> e[N], rev[N];

int n, m, cnt, sz[N];

int dfn[N], low[N], ins[N], bel[N], idx;
stack<int> stk;
vector<int> cc[N];
int f1[N], f2[N];

void dfs(int u) {
	dfn[u] = low[u] = ++idx;
	ins[u] = true;
	stk.push(u);
	for (auto v : e[u]) {
		if (!dfn[v]) dfs(v);
		if (ins[v]) low[u] = min(low[u], low[v]);
	}
	if (dfn[u] == low[u]) {
		++cnt;
		while (true) {
			int v = stk.top();
			ins[v] = false;
			bel[v] = cnt;
			sz[cnt]++;
			cc[cnt].push_back(v);
			stk.pop();
			if (v == u) break;
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		rev[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) 
		if (!dfn[i]) dfs(i);
	int c = bel[1];
	for (int i = 1; i <= cnt; i++) {
		f1[i] = f2[i] = -inf;
	}
	f1[c] = sz[c];
	for (int i = c - 1; i >= 1; i--) {
		//f1[i] = sz[i];
		for (auto u : cc[i]) for (auto v : rev[u]) {
			if (bel[v] > bel[u]) f1[i] = max(f1[i], f1[bel[v]] + sz[i]);
		}
	}
	f2[c] = sz[c];
	for (int i = c + 1; i <= cnt; i++) {
		//f2[i] = sz[i];
		for (auto u : cc[i]) for (auto v : e[u]) {
			if (bel[v] < bel[u]) f2[i] = max(f2[i], f2[bel[v]] + sz[i]);
		}
	}
	int ans = sz[c];
	for (int i = c; i <= cnt; i++)
		for (auto u : cc[i]) for (auto v : e[u]) {
			if (bel[v] <= c) ans = max(ans, f2[i] + f1[bel[v]] - sz[c]);
		}
	printf("%d\n", ans);
}
