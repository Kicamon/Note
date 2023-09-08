#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2010;
vector<int> e[N];

int dfn[N], low[N], ins[N], bel[N], idx, n, m, cnt;
int vis[N];
char ans[N];
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

void dfs2(int u) {
	vis[u] = 1;
	for (auto v : e[u]) if (!vis[v]) {
		dfs2(v);
	}
}

bool check(int s, int t) {
	memset(vis, 0, sizeof(vis));
	dfs2(s);
	return vis[t];
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		char ty1[2], ty2[2];
		int u, v;
		scanf("%d%s%d%s", &u, ty1, &v, ty2);
		--u; --v;
		u = u * 2 + (ty1[0] == 'Y');
		v = v * 2 + (ty2[0] == 'Y');
		e[u ^ 1].push_back(v);
		e[v ^ 1].push_back(u);
	}
	for (int i = 0; i < 2 * n; i++) if (dfn[i] == 0)
		dfs(i);
	for (int i = 0; i < n; i++) {
		if (bel[2 * i] == bel[2 * i + 1]) {
			puts("IMPOSSIBLE");
			return 0;
		}
	}
	for (int i = 0; i < n; i++) {
		if (check(2 * i, 2 * i + 1)) ans[i] = 'Y';
		else if (check(2 * i + 1, 2 * i)) ans[i] = 'N';
		else ans[i] ='?';
	}
	puts(ans);
}
