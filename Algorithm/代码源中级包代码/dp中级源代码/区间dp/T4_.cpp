#include <bits/stdc++.h>
using namespace std;
const int inf = 1 << 29;
const int N = 610;

int n, m, a[N], b[N], d[N], dp[N][N];

int solve(int l,int r) {
	if (l > r) return 0;
	if (dp[l][r] != -1) return dp[l][r];
	int &ans = dp[l][r];
	ans = inf;
	int maxd = -1, mxpos = -1;
	for (int i = 1; i <= n; i++) if (a[i] >= l && b[i] <= r) {
		if (d[i] > maxd) maxd = d[i], mxpos = i;
	}
	if (maxd == -1) return ans = 0;
	for (int i = a[mxpos]; i <= b[mxpos]; i++) {
		ans = min(ans, solve(l, i - 1) + solve(i + 1, r));
	}
	ans = ans + maxd;
	return ans;
}
void solve() {
	scanf("%d", &n);
	vector<int> v;
	for (int i = 1; i <= n; i++) {
		scanf("%d%d%d", &a[i], &b[i], &d[i]);
		v.push_back(a[i]);
		v.push_back(b[i]);
	}
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	m = v.size();
	for (int i = 1; i <= n; i++) {
		a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
		b[i] = lower_bound(v.begin(), v.end(), b[i]) - v.begin() + 1;
	}
	for (int i = 1; i <= m; i++)
		for (int j = i; j <= m; j++) dp[i][j] = -1;
	printf("%d\n", solve(1, m));
}

int main() {
	int tc;
	scanf("%d", &tc);
	for (int i = 1; i <= tc; i++) {
		solve();
	}
}