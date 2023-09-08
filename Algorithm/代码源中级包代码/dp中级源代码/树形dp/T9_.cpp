#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;

int n;
int dp[N][2], dep[N], f[N];

void solve() {
	scanf("%d",&n);
	for (int i = 2; i <= n; i++) {
		scanf("%d", &f[i]);
		dep[i] = dep[f[i]] + 1;
	}
	for (int i = 1; i <= n; i++) {
		dp[i][1] = dep[i];
		dp[i][0] = 0;
	}
	for (int v = n; v >= 2; v--) {
		int u = f[v];
		dp[u][1] = min(min(dp[u][1] + dp[v][1], dp[u][1] + dp[v][0] + 2), dp[u][0] + dp[v][1]);
		dp[u][0] += dp[v][0] + 2;
	}
	printf("%d\n", dp[1][1]);
}

int main() {
	int tc;
	scanf("%d",&tc);
	for (int i = 1; i <= tc; i++) {
		printf("Case #%d: ", i);
		solve();
	}
}