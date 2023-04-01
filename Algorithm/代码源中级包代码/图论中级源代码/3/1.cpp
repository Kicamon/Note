#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 5010;
int n, m, x[N];
vector<array<int, 3>> E;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		// u -> v w
		E.push_back({v, u, w});
	}
	for (int i = 1; i <= n; i++) {
		// 0 -> i 0
		E.push_back({i, 0, 0});
	}
	for (int i = 1; i <= n; i++)
		x[i] = 1 << 30;
	for (int i = 0; i <= n; i++) {
		for (auto [u, v, w] : E) {
			x[u] = min(x[u], x[v] + w);
		}
	}
	for (auto [u, v, w] : E) {
		if (x[u] > x[v] + w) {
			puts("-1");
			return 0;
		}
	}
	for (int i = 1; i <= n; i++)
		printf("%d ", x[0] - x[i]);
	puts("");
}