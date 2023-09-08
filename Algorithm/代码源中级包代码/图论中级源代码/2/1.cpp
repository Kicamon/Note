#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 101000;
vector<pair<int, int>> e[N];

int dfn[N], low[N], idx, n, m;
vector<int> bridge;

void dfs(int u, int id) {
	dfn[u] = low[u] = ++idx;
	for (auto [v, id2] : e[u]) {
		if (!dfn[v]) {
			dfs(v, id2);
			low[u] = min(low[u], low[v]);
			if (dfn[v] == low[v]) bridge.push_back(id2 + 1);
		} else if (id != id2) {
			low[u] = min(low[u], dfn[v]);
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back({v, i});
		e[v].push_back({u, i});
	}
	dfs(1, -1);
	sort(bridge.begin(), bridge.end());
	printf("%d\n", (int)bridge.size());
	for (auto x : bridge) printf("%d ",x);
	puts("");
}
