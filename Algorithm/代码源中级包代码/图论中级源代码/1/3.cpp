#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 101000;
vector<int> e[N];

int n, m, mod, cnt;

int dfn[N], low[N], ins[N], bel[N], idx;
stack<int> stk;
vector<int> vec[N];
int dp[N], way[N], vis[N], T, ans, w;

void dfs(int u) {
	dfn[u] = low[u] = ++idx;
	ins[u] = true;
	stk.push(u);
	for (auto v : e[u]) {
		if (!dfn[v]) dfs(v);
		if (ins[v]) low[u] = min(low[u], low[v]);
	}
	if (dfn[u] == low[u]) {
		++cnt;
		int sz = 0;
		dp[cnt] = 0;
		way[cnt] = 1;
		++T;
		vis[cnt] = T;
		while (true) {
			int v = stk.top();
			ins[v] = false;
			bel[v] = cnt;
			sz++;
			for (int w : e[v]) if (vis[bel[w]] != T && bel[w] != 0) {
				vis[bel[w]] = T;
				if (dp[bel[w]] > dp[cnt]) {
					dp[cnt] = dp[bel[w]];
					way[cnt] = 0;
				}
				if (dp[bel[w]] == dp[cnt]) {
					way[cnt] = (way[cnt] + way[bel[w]]) % mod;
				}
			}
			stk.pop();
			if (v == u) break;
		}
		dp[cnt] += sz;
		if (dp[cnt] > ans) ans = dp[cnt], w = 0;
		if (dp[cnt] == ans) w = (w + way[cnt]) % mod;
	}
}

int main() {
	scanf("%d%d%d", &n, &m, &mod);
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
	}
	for (int i = 1; i <= n; i++) 
		if (!dfn[i]) dfs(i);
	printf("%d\n%d\n", ans, w);
}
