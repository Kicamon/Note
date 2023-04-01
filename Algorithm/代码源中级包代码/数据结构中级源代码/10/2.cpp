#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 301000;
const int LOGN = 19;

int n, m, l[N], r[N], tot, W[N];
int dep[N], par[N][LOGN + 1];
vector<int> e[N];
vector<array<int, 3>> up, down;
int s[N * 2], ans[N];

void dfs(int u, int f) {
	l[u] = ++tot;
	dep[u] = dep[f] + 1;
	for (auto v : e[u]) {
		if (v == f) continue;
		par[v][0] = u;
		dfs(v, u);
	}
	r[u] = tot;
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

int main() {
	scanf("%d%d",&n, &m);
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
	for (int i = 1; i <= n; i++) scanf("%d", &W[i]);
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		int w = LCA(u, v);
		up.push_back({dep[u], l[u], 1});
		up.push_back({dep[u], l[w], -1});
		int T = dep[v] + dep[u] - 2 * dep[w];
		down.push_back({T - dep[v], l[v], 1});
		down.push_back({T - dep[v], l[w], -1});
		if (W[w] == dep[u] - dep[w]) ans[w]++;
	}
	m = up.size();
	sort(up.begin(), up.end());
	for (int i = 0; i < m; i++) {
		s[i + 1] = s[i] + up[i][2];
	}
	for (int v = 1; v <= n; v++) {
		// {W[v] + dep[v], l[v]} ... {W[v] + dep[v], r[v]} 权值和
		int pl = lower_bound(up.begin(), up.end(),
			array<int, 3>{W[v] + dep[v], l[v], -2}) - up.begin();
		int pr = lower_bound(up.begin(), up.end(),
			array<int, 3>{W[v] + dep[v], r[v], 2}) - up.begin();
		ans[v] += s[pr] - s[pl];
	}

	m = down.size();
	sort(down.begin(), down.end());
	for (int i = 0; i < m; i++) {
		s[i + 1] = s[i] + down[i][2];
	}
	for (int v = 1; v <= n; v++) {
		int pl = lower_bound(down.begin(), down.end(), 
			array<int, 3>{W[v] - dep[v], l[v], -2}) - down.begin();
		int pr = lower_bound(down.begin(), down.end(), 
			array<int, 3>{W[v] - dep[v], r[v], 2}) - down.begin();
		ans[v] += s[pr] - s[pl];
	}

	for (int i = 1; i <= n; i++) printf("%d%c", ans[i], " \n"[i == n]);
}