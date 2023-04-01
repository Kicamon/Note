#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1010000;
const ll inf = 1ll << 60;

int n, p[N], val[N];
vector<int> e[N];
ll dp[N][2], dp2[N][2], ans;
bool vis[N], oncyc[N];

void dfs(int u) {
	vis[u] = true;
	dp[u][1] = val[u];
	for (auto v : e[u]) {
		if (oncyc[v]) continue;
		dfs(v);
		dp[u][0] += max(dp[v][0], dp[v][1]);
		dp[u][1] += dp[v][0];
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &val[i], &p[i]);
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
		// 树形dp
		for (auto v : cyc) {
			dfs(v);
		}
		// 环上dp
		int m = cyc.size();
		ll ans2 = -inf;
		for (int t = 0; t < 2; t++) {
			// dp2[i][0/1]
			for (int j = 0; j < 2; j++) {
				if (j == t) dp2[0][j] = dp[cyc[0]][j];
				else dp2[0][j] = -inf;
			}
			for (int i = 1; i < m; i++) {
				int u = cyc[i];
				dp2[i][0] = max(dp2[i - 1][0], dp2[i - 1][1]) + dp[u][0];
				dp2[i][1] = dp2[i - 1][0] + dp[u][1];
			}
			if (t == 0) ans2 = max(ans2, max(dp2[m - 1][0], dp2[m - 1][1]));
			else ans2 = max(ans2, dp2[m - 1][0]);
		}
		ans += ans2;
	}
	printf("%lld\n", ans);
}
