#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 101000;
vector<int> e[N];

int dfn[N], low[N], ins[N], bel[N], idx, n, m, cnt;
stack<int> stk;
vector<vector<int>> scc;

void dfs(int u) {
	dfn[u] = low[u] = ++idx;
	ins[u] = true;
	stk.push(u);
	for (auto v : e[u]) {
		if (!dfn[v]) dfs(v);
		if (ins[v]) low[u] = min(low[u], low[v]);
	}
	if (dfn[u] == low[u]) {
		vector<int> c;
		++cnt;
		while (true) {
			int v = stk.top();
			c.push_back(v);
			ins[v] = false;
			bel[v] = cnt;
			stk.pop();
			if (v == u) break;
		}
		sort(c.begin(), c.end());
		scc.push_back(c);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) dfs(i);
	sort(scc.begin(), scc.end());
	for (auto c : scc) {
		for (auto u : c) printf("%d ", u);
		puts("");
	}
}
