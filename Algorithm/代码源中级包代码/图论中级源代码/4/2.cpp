#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1010000;
const ll inf = 1ll << 60;

int n, p[N], L[N];
vector<int> e[N];
ll dp[N], s[N], pre[N], suf[N], ans, maxd;
bool vis[N], oncyc[N];

void dfs(int u) {
	vis[u] = true;
	dp[u] = 0;
	for (auto v : e[u]) {
		if (oncyc[v]) continue;
		dfs(v);
		ll d = dp[v] + L[v];
		maxd = max(maxd, d + dp[u]);
		dp[u] = max(dp[u], d);
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &p[i], &L[i]);
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
		maxd = 0;
		// 树形dp
		for (auto v : cyc) {
			dfs(v);
		}
		// 环上dp
		int m = cyc.size();
		for (int i = 2; i <= m; i++) {
			s[i] = s[i - 1] + L[cyc[i - 2]];
		}
		ll totL = s[m] + L[cyc[m - 1]];
		pre[0] = -inf;
		for (int i = 1; i <= m; i++) {
			pre[i] = max(pre[i - 1], dp[cyc[i - 1]] - s[i]);
		}
		suf[m + 1] = -inf;
		for (int i = m; i >= 1; i--) {
			suf[i] = max(suf[i + 1], dp[cyc[i - 1]] - s[i]);
		}
		for (int i = 1; i <= m; i++) {
			maxd = max(maxd, pre[i - 1] + dp[cyc[i - 1]] + s[i]);
			maxd = max(maxd, suf[i + 1] + dp[cyc[i - 1]] + s[i] + totL);
		}
		ans += maxd;
	}
	printf("%lld\n", ans);
}
