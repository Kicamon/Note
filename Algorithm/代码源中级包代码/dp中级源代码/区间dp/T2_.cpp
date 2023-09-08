#include <bits/stdc++.h>
using namespace std;
const int inf = 1 << 29;
const int N = 5010;

int n, pos[N], a[N], nxt[N], dp[N][N];
void solve() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		pos[i] = n + 1;
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		if (i != 1 && a[i] == a[i - 1]) {
			--i; --n;
		}
	}
	for (int i = n; i >= 1; i--) {
		nxt[i] = pos[a[i]];
		pos[a[i]] = i;
	}
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j++) dp[i][j] = 0;

	// for (int l = n; l >= 1; l--) for (int r = l; r <= n; r++) 

	for (int d = 0 ; d < n; d++) {
		for (int l = 1; l + d <= n; l++) {
			int r = l + d;
			dp[l][r] = dp[l + 1][r];
			int x = nxt[l];
			while (x <= r) {
				dp[l][r] = max(dp[l][r], dp[l + 1][x - 1] + dp[x][r] + 1);
				x = nxt[x];
			}
		}
	}
	printf("%d\n", n - 1 - dp[1][n]);
}

int main() {
	int tc;
	scanf("%d", &tc);
	for (int i = 1; i <= tc; i++) {
		solve();
	}
}