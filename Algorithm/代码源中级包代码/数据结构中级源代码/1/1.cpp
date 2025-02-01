#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000;

int n, q;
int a[N];
ll c[N];

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
		modify(i, a[i]);
	}
	for (int i = 0; i < q; i++) {
		int ty;
		scanf("%d", &ty);
		if (ty == 1) {
			int x, d;
			scanf("%d%d", &x, &d);
			modify(x, d - a[x]);
			a[x] = d;
		} else {
			int x;
			scanf("%d", &x);
			printf("%lld\n", query(x));
		}
	}
}