#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 510;

int n, m, q;
int a[N][N];
ll c[N][N];

ll query(int x, int y) { // 1 ... x
	ll s = 0;
	for (int p = x; p; p -= p & (-p))
		for (int q = y; q; q -= q &(-q)) 
			s += c[p][q];
	return s;
}

void modify(int x, int y, ll s) { // a[x] += s
	for (int p = x; p <= n; p += p & (-p))
		for (int q = y; q <= m; q += q & (-q))
			c[p][q] += s;
} 

int main() {
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			scanf("%d", &a[i][j]);
			modify(i, j, a[i][j]);
		}
	for (int i = 0; i < q; i++) {
		int ty;
		scanf("%d", &ty);
		if (ty == 1) {
			int x, y, d;
			scanf("%d%d%d", &x, &y, &d);
			modify(x, y, d - a[x][y]);
			a[x][y] = d;
		} else {
			int x, y;
			scanf("%d%d", &x, &y);
			printf("%lld\n", query(x, y));
		}
	}
}