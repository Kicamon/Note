#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 101000;
vector<int> e[N], erev[N];

int vis[N], n, m;
stack<int> stk;
vector<vector<int>> scc;
vector<int> out, c;

void dfs(int u) {
	vis[u] = true;
	for (auto v : e[u]) {
		if (!vis[v]) dfs(v);
	}
	out.push_back(u);
}

void dfs2(int u) {
	vis[u] = true;
	for (auto v : erev[u]) {
		if (!vis[v]) dfs2(v);
	}
	c.push_back(u);
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		erev[v].push_back(u);
	}
	for (int i = 1; i <= n; i++)
		if (!vis[i]) dfs(i);
	reverse(out.begin(), out.end());
	memset(vis, 0, sizeof(vis));
	for (auto u : out) if (!vis[u]) {
		c.clear();
		dfs2(u);
		sort(c.begin(), c.end());
		scc.push_back(c);
	}
	sort(scc.begin(), scc.end());
	for (auto c : scc) {
		for (auto u : c) printf("%d ", u);
		puts("");
	}
}
