#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 301000;
const int LOGN = 19;

int n, a[N], val[N], tag[N];
int dep[N], par[N][LOGN + 1];
vector<int> e[N];

void dfs(int u, int f) {
	dep[u] = dep[f] + 1;
	for (auto v : e[u]) {
		if (v == f) continue;
		par[v][0] = u;
		dfs(v, u);
	}
}

int LCA(int u, int v) {
	if (dep[u] > dep[v]) swap(u, v);
	int d = dep[v] - dep[u];
	for (int j = LOGN; j >= 0; j--) if (d & (1 << j)) {
		v = par[v][j];
	}
	if (u == v) return u;
	for (int j = LOGN; j >= 0; j--) if (par[u][j] != par[v][j]) {
		u = par[u][j];
		v = par[v][j];
	}
	return par[u][0];
}

void dfs2(int u, int f) {
	for (auto v : e[u]) if (v !=f) {
		dfs2(v, u);
		tag[u] += tag[v];
	}
}

int main() {
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1, 0);
	for (int j = 1; j <= LOGN; j++) {
		for (int u = 1; u <= n; u++) {
			par[u][j] = par[par[u][j - 1]][j - 1];
		}
	}
	for (int i = 2; i <= n; i++) {
		int u = a[i - 1], v = a[i], w = LCA(u, v);
		tag[u]++;
		tag[v]++;
		tag[w] -= 2;
		val[w] += 1;
		val[v] -= 1;
	}
	dfs2(1, 0);
	for (int i = 1; i <= n; i++) printf("%d\n", tag[i] + val[i]);
}