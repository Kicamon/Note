#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=100010;

int n, mod;

vector<int> son[N];

ll dp[N], dp2[N], ans[N];

void dfs(int u) {
	dp[u] = 1;
	for (auto v : son[u]) {
		dfs(v);
		dp[u] = dp[u] * (dp[v] + 1) % mod;
	}
}

void dfs2(int u) {
	static ll pre[N], suf[N];

	int m = son[u].size();
	if (m == 0) return;

	pre[0] = 1;
	for (int i = 0; i < m; i++) {
		int v = son[u][i];
		pre[i + 1] = pre[i] * (dp[v] + 1) % mod;
	}

	suf[m] = 1;
	for (int i = m - 1; i >= 0; i--) {
		int v = son[u][i];
		suf[i] = suf[i + 1] * (dp[v] + 1) % mod;
	}

	for (int i = 0; i < m; i++) {
		int v = son[u][i];
		dp2[v] = pre[i] * suf[i + 1] % mod;
		if (u != 1) dp2[v] = dp2[v] * (dp2[u] + 1) % mod;
	}
	for (auto v : son[u]) {
		ans[v] = (dp2[v] + 1) * dp[v] % mod;
		dfs2(v);
	}
}

int main() {
	scanf("%d%d", &n, &mod);
	for (int i = 2; i <= n; i++) {
		int f;
		scanf("%d", &f);
		son[f].push_back(i);
	}
	dfs(1);
	dfs2(1);
	ans[1] = dp[1];
	for (int i = 1; i <= n; i++)
		printf("%lld\n", ans[i]);
}
