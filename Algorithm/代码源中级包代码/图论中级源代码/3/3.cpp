#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 101000;
vector<int> e[N];

int dfn[N], low[N], ins[N], bel[N], idx, n, m, cnt;
stack<int> stk;

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
			stk.pop();
			if (v == u) break;
		}
	}
}

void solve() {
	scanf("%d%d ", &n, &m);
	// 0 .. 2n-1  i,   mi   2 * i, hi 2 * i + 1
	for (int i = 0; i < 2 * n; i++)
		dfn[i] = 0, e[i].clear();
	idx = cnt = 0;
	for (int i = 0; i < m; i++) {
		char ty1, ty2;
		int u, v;
		scanf("%c%d %c%d ", &ty1, &u, &ty2, &v);
		--u; --v;
		u = u * 2 + (ty1 == 'h');
		v = v * 2 + (ty2 == 'h');
		e[u ^ 1].push_back(v);
		e[v ^ 1].push_back(u);
	}
	for (int i = 0; i < 2 * n; i++) if (dfn[i] == 0)
		dfs(i);
	for (int i = 0; i < n; i++) {
		// bel[2 * i] < bel [2 * i + 1] 选 2 * i
		if (bel[2 * i] == bel[2 * i + 1]) {
			puts("BAD");
			return;
		}
	}
	puts("GOOD");
}

int main() {
	int tc;
	scanf("%d", &tc);
	for (int i = 0; i < tc; i++) {
		solve();
	}
}
