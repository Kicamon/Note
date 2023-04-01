#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 610;
const int inf = 1 << 29;

int n, m1, m2;
int g[N][N];
bool vis[N];

int main() {
	scanf("%d%d%d", &n, &m1, &m2);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			g[i][j] = (i == j) ? 0 : inf;
		}
	}
	for (int i = 1; i <= m1; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		g[b][a] = min(g[b][a], -1);
		g[a][b] = min(g[a][b], 1);
	}

	for (int i = 1; i <= m2; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		g[b][a] = min(g[b][a], 0);
	}
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
	for (int i = 1; i <= n; i++)
		if (g[i][i] < 0) {
			puts("NIE");
			return 0;
		}
	int ans = 0;
	for (int i = 1; i <= n; i++) if (!vis[i]) {
		vector<int> v;
		for (int j = 1; j <= n; j++)
			if (g[i][j] <= n && g[j][i] <= n) {
				v.push_back(j);
				vis[j] = true;
			}
		int d = 0;
		for (auto p : v)for (auto q : v)
			d = max(d, g[p][q]);
		ans += d + 1;
	}
	printf("%d\n", ans);
}