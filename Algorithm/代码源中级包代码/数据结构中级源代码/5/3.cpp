#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000;
ll tmp, ans[N], ans2[N];
int n, q, c[N], cnt[N];
array<int, 3> que[N];

ll gcd(ll a, ll b) {
	if (b == 0) return a;
	else return gcd(b, a % b);
}

int main() {
	scanf("%d%d",&n, &q);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &c[i]);
	}
	for (int i = 0; i < q; i++) {
		int l, r;
		scanf("%d%d", &l, &r);
		que[i] = {l, r, i};
		ans2[i] = (ll)(r - l) * (r - l + 1) / 2;
	}
	int B = 500;
	sort(que, que + q, [&](array<int, 3> a, array<int, 3> b) {
		int c = a[0] / B;
		if (c != b[0] / B) return c < b[0] / B;
		return c % 2 ? a[1] > b[1] : a[1] < b[1];
	});
	int l = 1, r = 0;
	auto add = [&] (int x) {
		tmp += cnt[c[x]];
		cnt[c[x]]++;
	};
	auto del = [&] (int x) {
		cnt[c[x]]--;
		tmp -= cnt[c[x]];
	};

	for (int i = 0; i < q; i++) {
		while (r < que[i][1]) r++, add(r);
		while (l > que[i][0]) l--, add(l);
		while (r > que[i][1]) del(r), r--;
		while (l < que[i][0]) del(l), l++;
		ans[que[i][2]] = tmp;
	}
	for (int i = 0; i < q; i++) {
		ll d = gcd(ans[i], ans2[i]);
		printf("%lld/%lld\n", ans[i] / d, ans2[i] / d);
	}
}