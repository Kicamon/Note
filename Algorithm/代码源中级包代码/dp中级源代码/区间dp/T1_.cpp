#include <bits/stdc++.h>
using namespace std;
const int inf = 1 << 29;
const int N = 110;

int n, L, R;
int a[N], s[N], dp[N][N][N];
void solve() {
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		s[i] = s[i - 1] + a[i];
	}
	for (int l = 1; l <= n; l++) 
		for (int r = l; r <= n; r++)
			for (int k = 1; k <= n; k++) {
				dp[l][r][k] = inf;
			}
	for (int d = 0; d <= n - 1; d++) {
		for (int l = 1; l + d <= n; l++) {
			int r = l + d;
			if (d == 0) {
				dp[l][r][1] = 0;
			} else {
				for (int k = 2; k <= n; k++) {
					for (int mid = l; mid < r; mid++)
						dp[l][r][k] = min(dp[l][r][k], dp[l][mid][1] + dp[mid + 1][r][k - 1]);
					if (k >= L && k <= R) dp[l][r][1] = min (dp[l][r][1], dp[l][r][k]);
				}
				dp[l][r][1] += s[r] - s[l - 1];
			}
		}
	}
	if (dp[1][n][1] >= inf) printf("0\n");
	else printf("%d\n", dp[1][n][1]);
}

int main() {
	while (scanf("%d%d%d",&n, &L, &R)!=EOF) {
		solve();
	}
}