#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000, M = 1000100;
int n, sz[N], maxs[N], L;
vector<pair<int, int>> e[N];
bool del[N];
int ans;
int dis[M], mark[M], T;

void solve(int u, int s) {
	int ms = s + 1, root = -1;
	function<void(int, int)> dfs1 = [&](int u, int par) {
		sz[u] = 1;
		maxs[u] = 0;
		for (auto [v, w]: e[u]) {
			if (del[v] || v == par) continue;
			dfs1(v, u);
			sz[u] += sz[v];
			maxs[u] = max(maxs[u], sz[v]);
		}
		maxs[u] = max(maxs[u], s - sz[u]);
		if (maxs[u] < ms) ms = maxs[u], root = u;
	};
	dfs1(u, -1);
	++T;
	dis[0] = 0;
	mark[0] = T;
	for (auto [v, w] : e[root]) {
		if (del[v]) continue;
		vector<pair<ll, int>> d;
		function<void(int, int, ll, int)> dfs2 = [&](int u, int par, ll dep, int d2) {
			if (dep > L) return;
			d.push_back(make_pair(dep, d2));
			for (auto [v, w] : e[u]) {
				if (del[v] || v == par) continue;
				dfs2(v, u, dep + w, d2 + 1);
			}
		};
		dfs2(v, root, w, 1);
		for (auto [d1, d2] : d) {
			if (mark[L - d1] == T) {
				ans = min(ans, dis[L - d1] + d2);
			}
		}
		for (auto [d1, d2] : d) {
			if (mark[d1] != T) dis[d1] = d2;
			else dis[d1] = min(dis[d1], d2);
			mark[d1] = T;
		}
	}
	del[root] = true;
	for (auto [v, w] : e[root]) {
		if (!del[v]) solve(v, sz[v]);
	}
}

int main() {
	scanf("%d%d", &n, &L);
	ans = n + 1;
	for (int i = 1; i < n; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		++u; ++v;
		e[u].push_back(make_pair(v, w));
		e[v].push_back(make_pair(u, w));
	}
	solve(1, n);
	if (ans > n) ans = -1;
	printf("%d\n", ans);
}