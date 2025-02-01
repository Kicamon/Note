#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000;
int n, sz[N], maxs[N];
vector<pair<int, int>> e[N];
bool del[N];
ll ans;
int cnt[N * 2], c[N * 2][2];

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
	cnt[s] = 1;
	for (auto [v, w] : e[root]) {
		if (del[v]) continue;
		vector<pair<int, bool>> d;
		function<void(int, int, int)> dfs2 = [&](int u, int par, int dep) {
			d.push_back(make_pair(dep, cnt[s + dep] != 0));
			if (dep == 0 && cnt[s] > 1) ans += 1;
			cnt[s + dep] += 1;
			for (auto [v, w] : e[u]) {
				if (del[v] || v == par) continue;
				dfs2(v, u, dep + w);
			}
			cnt[s + dep] -= 1;
		};
		dfs2(v, root, w);
		for (auto [d1, d2] : d) {
			if (d2) ans += c[s - d1][0] + c[s - d1][1];
			else ans += c[s - d1][1];
		}
		for (auto [d1, d2] : d) {
			c[s + d1][d2] += 1;
		}
	}
	cnt[s] = 0;
	for (int i = 0; i <= 2 * s; i++) c[i][0] = c[i][1] = 0;
	del[root] = true;
	for (auto [v, w] : e[root]) {
		if (!del[v]) solve(v, sz[v]);
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		if (w == 0) w = -1;
		e[u].push_back(make_pair(v, w));
		e[v].push_back(make_pair(u, w));
	}
	solve(1, n);
	printf("%lld\n", ans);
}