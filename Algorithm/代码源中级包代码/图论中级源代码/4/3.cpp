#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1010000;
const ll inf = 1ll << 60;

int n, p[N], c[N];
vector<int> e[N];
ll cost;
bool vis[N], oncyc[N], del[N];

void dfs(int u) {
	vis[u] = true;
	for (auto v : e[u]) {
		if (oncyc[v]) continue;
		dfs(v);
	}
	sort(e[u].begin(), e[u].end(), [&](int a, int b) {
		return c[a] < c[b];
	});
	int m = e[u].size();
	for (int i = 0; i < m - 1; i++) {
		cost += c[e[u][i]];
		del[e[u][i]] = true;
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &p[i], &c[i]);
		e[p[i]].push_back(i);
	}
	for (int i = 1; i <= n; i++) if (!vis[i]) {
		// 往前跳，找到环上的点
		int u = i;
		while (!vis[u]) {
			vis[u] = true;
			u = p[u];
		}
		// 找到整个环
		int v = u;
		vector<int> cyc;
		while (true) {
			cyc.push_back(v);
			oncyc[v] = true;
			v = p[v];
			if (v == u) break;
		}
		if (cyc.size() == n) {
			printf("0\n");
			return 0;
		}
		// 树形dp
		for (auto v : cyc) {
			dfs(v);
		}
		bool cycdel = false;
		for (auto v : cyc) {
			cycdel |= del[v];
		}
		if (!cycdel) {
			ll extra = inf;
			for (auto v : cyc) {
				int m = e[v].size();
				extra = min(extra, (ll)c[e[v][m - 1]] - (m == 1? 0 : c[e[v][m - 2]]));
			}
			cost += extra;
		}
	}
	printf("%lld\n", cost);
}
