#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 101000;
vector<int> e[N];

int dfn[N], low[N], ins[N], bel[N], sz[N], idx, n, m, cnt;
stack<int> stk;
int outd[N];

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
		while (true) {
			int v = stk.top();
			ins[v] = false;
			bel[v] = cnt;
			sz[cnt] ++;
			stk.pop();
			if (v == u) break;
		}
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
	for (int u = 1; u <= n; u++)
		for (auto v : e[u]) {
			if (bel[u] != bel[v]) outd[bel[u]]++;
		}
	int cnts = 0, cntv = 0;
	for (int i = 1; i <= cnt; i++) {
		if (outd[i] == 0) {
			cnts++;
			cntv += sz[i];
		}
	}
	if (cnts >= 2) {
		puts("0");
	} else {
		printf("%d\n", cntv);
	}
}
