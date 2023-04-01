#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1010000;
const int mod = 998244353;

int n, p[N], c[N], dfn[N], idx;
int rev[N], totrev;
vector<pair<int, int>> e[N];
vector<int> vec;
vector<array<int, 3>> cyc;
ll cost;

void dfs(int u, int id) {
	dfn[u] = ++idx;
	vec.push_back(u);
	for (auto [v, id2] : e[u]) {
		if (!dfn[v]) {
			totrev += id2 % 2;
			rev[v] = rev[u] + (id2 % 2 == 1 ? -1: 1);
			dfs(v, id2);
		} else if (id2 != (id ^ 1) && dfn[v] <= dfn[u]) {
			cyc.push_back({u, v, id2});
		}
	}
}

void solve() {
	scanf("%d", &n);
	for (int i = 1; i <= 2 * n; i++) {
		e[i].clear();
		dfn[i] = 0;
	}
	idx = 0;
	for (int i = 0; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[v].push_back({u, 2 * i});
		if (u != v) e[u].push_back({v, 2 * i + 1});
	}
	int ans1 = 0;
	int ans2 = 1;
	for (int i = 1; i <= 2 * n; i++) if (!dfn[i]) {
		vec.clear();
		cyc.clear();
		rev[i] = 0;
		totrev = 0;
		dfs(i, -1);
		if (cyc.size() >= 2) {
			puts("-1 -1");
			return;
		} else if (cyc.size() == 0) {
			int minrev = 1 << 30, way = 0;
			for (auto u : vec) {
				if (rev[u] < minrev) minrev = rev[u], way = 0;
				if (rev[u] == minrev) way++;
			}
			ans1 += totrev + minrev;
			ans2 = (ll)ans2 * way % mod;
		} else {
			int rev1 = totrev + rev[cyc[0][0]] + 1 - cyc[0][2] % 2;
			int rev2 = totrev + rev[cyc[0][1]] + cyc[0][2] % 2;
			int way = 1;
			if (rev1 == rev2) way++;
			ans1 += min(rev1, rev2);
			ans2 = (ll)ans2 * way % mod;
		}
	}
	printf("%d %d\n", ans1, ans2);
}

int main() {
	int tc;
	scanf("%d", &tc);
	for (int i = 0; i < tc; i++) {
		solve();
	}
}
