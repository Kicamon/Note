#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000;
const int LOGN = 18;

int n, q;
int dep[N], par[N][LOGN + 1], val[N][LOGN + 1];
vector<pair<int, int>> e[N];

void dfs(int u, int f) {
	dep[u] = dep[f] + 1;
	for (auto p : e[u]) {
		int v = p.first;
		if (v == f) continue;
		par[v][0] = u;
		val[v][0] = p.second;
		dfs(v, u);
	}
}

int query(int u, int v) {
	int ans = 1 << 30;
	if (dep[u] > dep[v]) swap(u, v);
	int d = dep[v] - dep[u];
	for (int j = LOGN; j >= 0; j--) if (d & (1 << j)) {
		ans = min(ans, val[v][j]);
		v = par[v][j];
	}
	if (u == v) return ans;
	for (int j = LOGN; j >= 0; j--) if (par[u][j] != par[v][j]) {
		ans = min(ans, min(val[u][j], val[v][j]));
		u = par[u][j];
		v = par[v][j];
	}
	ans = min(ans, min(val[u][0], val[v][0]));
	return ans;
}

int main() {
	scanf("%d%d",&n, &q);
	for (int i = 1; i < n; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		e[u].push_back(make_pair(v, w));
		e[v].push_back(make_pair(u, w));
	}
	dfs(1, 0);
	for (int j = 1; j <= LOGN; j++) {
		for (int u = 1; u <= n; u++) {
			par[u][j] = par[par[u][j - 1]][j - 1];
			val[u][j] = min(val[u][j - 1], val[par[u][j - 1]][j - 1]);
		}
	}
	for (int i = 1; i <= q; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		printf("%d\n", query(u, v));
	}
}