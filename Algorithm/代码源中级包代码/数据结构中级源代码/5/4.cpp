#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000;
int n, q, c[N], cnt[N], freq[N], ans[N];
array<int, 4> que[N];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &c[i]);
	}
	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		int l, r, k;
		scanf("%d%d%d", &l, &r, &k);
		que[i] = {l, r, k, i};
	}
	int B = 500;
	sort(que, que + q, [&](array<int, 4> a, array<int, 4> b) {
		int c = a[0] / B;
		if (c != b[0] / B) return c < b[0] / B;
		return c % 2 ? a[1] > b[1] : a[1] < b[1];
	});
	int l = 1, r = 0;
	auto add = [&] (int x) {
		cnt[freq[c[x]]]--;
		freq[c[x]]++;
		cnt[freq[c[x]]]++;
	};
	auto del = [&] (int x) {
		cnt[freq[c[x]]]--;
		freq[c[x]]--;
		cnt[freq[c[x]]]++;
	};

	for (int i = 0; i < q; i++) {
		while (r < que[i][1]) r++, add(r);
		while (l > que[i][0]) l--, add(l);
		while (r > que[i][1]) del(r), r--;
		while (l < que[i][0]) del(l), l++;
		ans[que[i][3]] = cnt[que[i][2]];
	}
	for (int i = 0; i < q; i++) {
		printf("%d\n", ans[i]);
	}
}