#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define left asfads
#define right sdfasdf

const int N = 501000;
int n, k;
int l[N], r[N], pos[N], left[N], right[N];
ll ans;

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) {
		int p;
		scanf("%d", &p);
		pos[p] = i;
	}
	for (int i = 0; i <= n + 1; i++) {
		l[i] = max(i - 1, 0);
		r[i] = min(i + 1, n + 1);
	}
	for (int i = 1; i <= n; i++) {
		int x = pos[i];
		left[0] = x;
		for (int j = 1; j <= k; j++) {
			x = l[x];
			left[j] = x;
		}
		x = pos[i];
		right[0] = x;
		for (int j = 1; j <= k ;j++) {
			x = r[x];
			right[j] =x;
		}
		x = pos[i];
		l[r[x]] = l[x];
		r[l[x]] = r[x];
		ll seg = 0;
		//for (int j = 0; j <= k; j++) printf("val %d left %d right %d\n",j, left[j],right[j]);
		for (int j = 1; j <= k; j++) {
			seg += 1ll * (left[j - 1] - left[j]) * (right[k - j + 1] - right[k - j]);
		}
		//printf("%d %lld\n", i, seg);
		ans += seg * i;
	}
	printf("%lld\n", ans);
}