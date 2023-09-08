#include <bits/stdc++.h>
using namespace std;

const int N=1000010;

vector<int> son[N];

int n;
int dp[N][2], dep[N];

void dfs(int u) {
	dp[u][1] = dep[u];
	dp[u][0] = 0;
	for (auto v:son[u]) {
		dep[v] = dep[u] + 1;
		dfs(v);
		dp[u][1] = min({dp[u][1] + dp[v][1], dp[u][1] + dp[v][0] + 2, dp[u][0] + dp[v][1]});
		dp[u][0] += dp[v][0] + 2;
	}
}

void solve() {
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) {
		son[i].clear();
	}
	for (int i = 2; i <= n; i++) {
		int f;
		scanf("%d", &f);
		son[f].push_back(i);
	}
	dfs(1);
	printf("%d\n", min(dp[1][0], dp[1][1]));
}

int main() {
	int tc;
	scanf("%d",&tc);
	for (int i = 1; i <= tc; i++) {
		printf("Case #%d: ", i);
		solve();
	}
}