#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000;

int n, q;
int a[N];
ll c[N];

void modify(int x, ll s) { // a[x] += s
	for (; x <= n; x += x & (-x)) {
		c[x] += s;
	}
} 

/*int query(ll s) {
	ll t = 0;
	int pos = 0;
	for (int j = 18; j >= 0; j--)
		if (pos + (1 << j) <= n && t + c[pos + (1 << j)] <= s) {
			pos += (1 << j);
			t += c[pos];
		}
	return pos;
}*/


int query(ll s) {
	int pos = 0;
	for (int j = 18; j >= 0; j--)
		if (pos + (1 << j) <= n && c[pos + (1 << j)] <= s) {
			pos += (1 << j);
			s -= c[pos];
		}
	return pos;
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
			ll s;
			scanf("%lld", &s);
			printf("%d\n", query(s));
		}
	}
}