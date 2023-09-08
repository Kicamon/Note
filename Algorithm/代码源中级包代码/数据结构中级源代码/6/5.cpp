#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000;
const int M = 500;
int n, q;
vector<int> p[N], large;
ll sum[M + 50][M + 50];

int main() {
	scanf("%d%d", &n, &q);
	for (int i = 0; i < q; i++) {
		int ty, x;
		scanf("%d%d", &ty, &x);
		if (ty == 1) {
			int y;
			scanf("%d", &y);
			int m = p[x].size();
			if (m <= M) {
				for (int j = 0; j < m; j++) sum[m][j] -= p[x][j];
			}
			p[x].push_back(y);
			++m;
			if (m <= M) {
				for (int j = 0; j < m; j++) sum[m][j] += p[x][j];
			} else if (m == M + 1) large.push_back(x);
		} else {
			ll ans = 0;
			for (int j = 1; j <= M; j++) ans += sum[j][x % j];
			for (auto y : large) {
				ans += p[y][x % (int)p[y].size()];
			}
			printf("%lld\n", ans);
		}
	}
}