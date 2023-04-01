#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 5010;
const int M = (1 << 20) + 10;

int n, a[N], cnt[M];
ll ans;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int b3 = 1; b3 <= n; b3++) {
		for (int b4 = b3 + 1; b4 <= n; b4++)
			ans += cnt[a[b3] ^ a[b4]];
		for (int b1 = 1; b1 < b3; b1++)
			cnt[a[b1] ^ a[b3]]++;
	}
	printf("%lld\n", ans);
}