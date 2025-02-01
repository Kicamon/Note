#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000;

int n;
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
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		a[i] = n + 1 - a[i];
	}
	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += query(a[i]);
		modify(a[i], 1);
	}
	printf("%lld\n", ans);
}