#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, a[30][30];
int wt[30];
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			scanf("%d", &a[i][j]);
		}
	int ans = 1e9;
	for (int S = 1; S < (1 << n); S++) {
		for (int j = 0; j < n; j++)
			wt[j] = 0;
		for (int i = 0; i < n; i++) if (S & (1 << i)) {
			for (int j = 0; j < n; j++) wt[j] += a[i][j];
		}
		sort(wt, wt + n);
		int t = n - __builtin_popcount(S) + 1;
		int s = 0;
		for (int j = 0; j < t; j++) s += wt[j];
		ans = min(ans, s);
	}
	printf("%d\n", ans);
}