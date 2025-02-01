#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 101000;

int n, k;
vector<pair<int,int>> e[N];
int l[N], r[N], id[N], sz[N], hs[N], tot, c[N];

int dep1[N];
ll dep2[N];

int ans;
map<ll, int> val;

void dfs_init(int u,int f) {
	l[u] = ++tot;
	id[tot] = u;
	sz[u] = 1;
	hs[u] = -1;
	for (auto [v, w] : e[u]) {
		if (v == f) continue;
		dep1[v] = dep1[u] + 1;
		dep2[v] = dep2[u] + w;
		dfs_init(v, u);
		sz[u] += sz[v];
		if (hs[u] == -1 || sz[v] > sz[hs[u]])
			hs[u] = v;
	}
	r[u] = tot;
}

void dfs_solve(int u, int f, bool keep) {
	for (auto [v, w] : e[u]) {
		if (v != f && v != hs[u]) {
			dfs_solve(v, u, false);
		}
	}
	if (hs[u] != -1) {
		dfs_solve(hs[u], u, true);
	}
	auto query = [&](int w) {
		ll d2 = k  +  2 * dep2[u] - dep2[w];
		if (val.count(d2)) {
			ans = min(ans, val[d2] + dep1[w] - 2 * dep1[u]);
		}
	};
	auto add = [&](int w) {
		if (val.count(dep2[w]))
			val[dep2[w]] = min(val[dep2[w]], dep1[w]);
		else 
			val[dep2[w]] = dep1[w];	
	};

	for (auto [v, w] : e[u]) {
		if (v != f && v != hs[u]) {
			for (int x = l[v]; x <= r[v]; x++)
				query(id[x]);
			for (int x = l[v]; x <= r[v]; x++)
				add(id[x]);
		}
	}
	query(u); add(u);
	if (!keep) {
		val.clear();
	}
}

int main(){
	scanf("%d%d", &n, &k);
	for (int i = 1; i < n; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		++u; ++v;
		e[u].push_back({v, w});
		e[v].push_back({u, w});
	}
	ans = n + 1;
	dfs_init(1, 0);
	dfs_solve(1, 0, false);
	if (ans >= n + 1) ans = -1;
	printf("%d\n", ans);
}
