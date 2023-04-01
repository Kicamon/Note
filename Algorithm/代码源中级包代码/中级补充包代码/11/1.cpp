#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 101000;
int n, sz[N], maxs[N], L;
vector<pair<int, int>> e[N];
bool del[N];
ll ans;

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
	vector<int> d1, d2;
	d1.push_back(0);
	auto calc = [&](vector<int> &d) {
		sort(d.begin(), d.end());
		int m = d.size();
		int r = m - 1;
		ll ans = 0;
		for (int i = 0; i < m; i++) {
			while (r >= 0 && d[i] + d[r] > L) --r;
			if (i < r) ans += r - i;
		}
		return ans;
	};
	for (auto [v, w] : e[root]) {
		if (del[v]) continue;
		d2.clear();
		function<void(int, int, int)> dfs2 = [&](int u, int par, int dep) {
			d1.push_back(dep);
			d2.push_back(dep);
			for (auto [v, w] : e[u]) {
				if (del[v] || v == par) continue;
				dfs2(v, u, dep + w);
			}
		};
		dfs2(v, root, w);
		ans -= calc(d2);
	}
	ans += calc(d1);
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
		e[u].push_back(make_pair(v, w));
		e[v].push_back(make_pair(u, w));
	}
	scanf("%d", &L);
	solve(1, n);
	printf("%lld\n", ans);
}