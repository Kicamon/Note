#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 100010, M = 100000;
int ans[N];
int n, q, a[N], cnt[N];
bitset<N> s, t;
array<int, 5> que[N];

int main() {
	scanf("%d%d",&n, &q);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 0; i < q; i++) {
		int l, r, opt, x;
		scanf("%d%d%d%d", &opt, &l, &r, &x);
		que[i] = {l, r, i, opt, x};
	}
	int B = 500;
	sort(que, que + q, [&](array<int, 5> a, array<int, 5> b) {
		int c = a[0] / B;
		if (c != b[0] / B) return c < b[0] / B;
		return c % 2 ? a[1] > b[1] : a[1] < b[1];
	});
	int l = 1, r = 0;
	auto add = [&] (int x) {
		cnt[a[x]]++;
		if (cnt[a[x]] == 1) {
			s[a[x]] = 1;
			t[M - a[x]] = 1;
		}
	};
	auto del = [&] (int x) {
		cnt[a[x]]--;
		if (cnt[a[x]] == 0) {
			s[a[x]] = 0;
			t[M - a[x]] = 0;
		}
	};

	for (int i = 0; i < q; i++) {
		while (r < que[i][1]) r++, add(r);
		while (l > que[i][0]) l--, add(l);
		while (r > que[i][1]) del(r), r--;
		while (l < que[i][0]) del(l), l++;
		int id = que[i][2], x = que[i][4];;
		if (que[i][3] == 1) {
			ans[id] = (s & (s << x)).any();
		} else if (que[i][3] == 2) {
			ans[id] = (t & (s << (M - x))).any();
		} else {
			for (int y = 1; y * y <= x; y++) if (x % y == 0)
				ans[id] |= s[y] && s[x / y];
		}
	}
	for (int i = 0; i < q; i++) {
		puts(ans[i] ? "yuno" : "yumi");
	}
}