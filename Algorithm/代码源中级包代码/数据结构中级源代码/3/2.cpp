#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000;

int n, q, a[N], pos[N];
vector<pair<int,int>> qu[N];

ll c[N], ans[N];

ll query(int x) { // 1 ... x
	ll s = 0;
	for (; x; x -= x & (-x)) {
		s += c[x];
	}
	return s;
}

void modify(int x, ll s) { // a[x] += s
	for (; x <= n; x += x & (-x)) {
		c[x] += s;
	}
} 

int main() {
	scanf("%d%d", &n, &q);

	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= q;i++) {
		int l, r;
		scanf("%d%d", &l, &r);
		qu[r].push_back({l, i});
	}
	for (int r = 1; r <= n; r++) {
		int p = pos[a[r]];
		modify(p + 1, a[r]);
		modify(r + 1, -a[r]);
		pos[a[r]] = r;
		for (auto que : qu[r]) {
			ans[que.second] = query(que.first);
		}
	}
	for (int i = 1; i <= q; i++) {
		printf("%lld\n", ans[i]);
	}
}