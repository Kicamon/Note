#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 101000;

int n, m;
vector<int> e[N];
int l[N], r[N], id[N];
int sz[N], hs[N], tot, top[N], dep[N], fa[N];

// 第一遍DFS，子树大小，重儿子，父亲，深度
void dfs1(int u,int f) {
	sz[u] = 1;
	hs[u] = -1;
	fa[u] = f;
	dep[u] = dep[f] + 1;
	for (auto v : e[u]) {
		if (v == f) continue;
		dfs1(v, u);
		sz[u] += sz[v];
		if (hs[u] == -1 || sz[v] > sz[hs[u]])
			hs[u] = v;
	}
}

// 第二遍DFS，每个点DFS序，重链上的链头的元素。
void dfs2(int u, int t) {
	top[u] = t;
	l[u] = ++tot;
	id[tot] = u;
	if (hs[u] != -1) {
		dfs2(hs[u], t);
	}
	for (auto v : e[u]) {
		if (v != fa[u] && v != hs[u]) {
			dfs2(v, v);
		}
	}
	r[u] = tot;
}

int LCA(int u, int v) {
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) v = fa[top[v]];
		else u = fa[top[u]];
	}
	if (dep[u] < dep[v]) return u;
	else return v;
}

int main(){
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs1(1, 0);
	dfs2(1, 1);
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		printf("%d\n", LCA(u, v));
	}
}
