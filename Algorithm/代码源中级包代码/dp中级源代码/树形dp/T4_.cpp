#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=2010;
const ll inf = 1ll<<60;


int n, m, f[N], dep[N];

vector<int> son[N];
vector<array<int, 3>> path[N];

ll dp[N], sdp[N];

void dfs(int u) {
	for (auto v : son[u]) {
		dfs(v);
		sdp[u] += dp[v];
	}
	dp[u] = sdp[u];
	for (auto p : path[u]) {
		ll tmp = sdp[u];
		int x = p[0];
		while (x != u) {
			tmp += sdp[x] - dp[x];
			x = f[x];
		}
		x = p[1];
		while (x != u) {
			tmp += sdp[x] - dp[x];
			x = f[x];
		}
		tmp += p[2];
		dp[u] = max(dp[u], tmp);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 2; i <= n; i++) {
		scanf("%d", &f[i]);
		son[f[i]].push_back(i);
		dep[i] = dep[f[i]] + 1;
	}
	for (int i = 1; i <= m; i++) {
		int u, v, a;
		scanf("%d%d%d", &u, &v, &a);
		int x = u, y = v;
		while (x != y) {
			if (dep[x] > dep[y]) x = f[x];
			else y = f[y];
		}
		path[x].push_back({u, v, a});
	}
	dfs(1);
	printf("%lld\n", dp[1]);
}
