#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 5010;

int n, m, dfn[N], idx, par[N], pe[N], del;
vector<pair<int, int>> e[N];
vector<int> cyc, ans, ord;

void dfs(int u, int id) {
	dfn[u] = ++idx;
	for (auto [v, id2] : e[u]) {
		if (!dfn[v]) {
			par[v] = u;
			pe[v] = id2;
			dfs(v, id2);
		} else if (id2 != id && dfn[v] <= dfn[u]) {
			int w = u;
			while (w != v) {
				cyc.push_back(pe[w]);
				w = par[w];
			}
			cyc.push_back(id);
		}
	}
}
void solve(int u, int par) {
	ord.push_back(u);
	for (auto [v, id] : e[u]) {
		if (v == par || id == del) continue;
		solve(v, u);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[v].push_back({u, i});
		e[u].push_back({v, i});
	}
	for (int i = 1; i <= n; i++) {
		sort(e[i].begin(), e[i].end());
	}
	if (n == m) {
		dfs(1, -1);
	}
	if (m == n - 1) {
		del = -1;
		solve(1, 0);
		ans = ord;
	}
	for (auto d : cyc) {
		del = d;
		ord.clear();
		solve(1, 0);
		if (ans.empty()) ans = ord;
		else ans = min(ans, ord);
	}
	for (auto x : ans) printf("%d ", x);
	puts("");
}
