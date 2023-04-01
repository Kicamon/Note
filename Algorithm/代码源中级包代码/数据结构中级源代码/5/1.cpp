#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000;
const int M = 500;
int n, q;
ll tag[M + 5][M + 5], val[N];
int main() {
	scanf("%d%d", &n, &q);
	for (int i = 0; i < q; i++) {
		int ty, x;
		scanf("%d%d", &ty, &x);
		if (ty == 1) {
			int y, d;
			scanf("%d%d", &y, &d);
			if (x <= M) {
				tag[x][y] += d;
			} else {
				for (int j = y; j <= n; j += x) {
					val[j] += d;
				}
			}
		} else {
			ll ans = val[x];
			for (int j = 1; j <= M; j++)
				ans += tag[j][x % j];
			printf("%lld\n", ans);
		}
	}
}