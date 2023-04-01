#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000;
const int M = 200000;

int n, a[N];
ll c[N], dp[N], ans;

ll query(int x) {
	ll s = 0;
	for (; x; x -= x & (-x))
		s = max(s, c[x]);
	return s;
}
void modify(int x, ll s) {
	for (; x <= M; x += x & (-x))
		c[x] = max(c[x], s);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d" ,&a[i]);
	}
	for (int i = 1; i <= n; i++) {
		// < a[i]
		dp[i] = query(a[i] - 1) + a[i];
		modify(a[i], dp[i]);
		ans = max(ans, dp[i]);
	}
	printf("%lld\n", ans);
}