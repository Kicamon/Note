#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 101000;

int n, m, w[N];
vector<int> e[N];
int l[N], r[N], idx[N];
int sz[N], hs[N], tot, top[N], dep[N], fa[N];

struct info {
	int lc, rc, seg;
};

info operator + (const info &l, const info &r) {
	return (info){l.lc, r.rc, l.seg + r.seg + (l.rc != r.lc)};
}

struct node {
	info val;
	int t;
} seg[N * 4];

// [l, r]

void settag(int id, int t) {
	seg[id].val = {t, t, 0};
	seg[id].t = t;
}

void pushdown(int id) {
	if (seg[id].t != 0) { // 标记非空
		settag(id * 2, seg[id].t);
		settag(id * 2 + 1, seg[id].t);
		seg[id].t = 0;
	}
}

void update(int id) {
	seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}

void build(int id, int l, int r) {
	if (l == r) {
		// l号点， DFS序中第l个点‼️
		seg[id].val = {w[idx[l]], w[idx[l]], 0};
	} else {
		int mid = (l + r) / 2;
		build(id * 2, l, mid);
		build(id * 2 + 1, mid + 1, r);
		update(id);
	}
}

void modify(int id, int l, int r, int ql, int qr, int t) {
	if (l == ql && r == qr) {
		settag(id, t);
		return;
	}
	int mid = (l + r) / 2;
	pushdown(id);
	if (qr <= mid) modify(id * 2, l, mid, ql, qr, t);
	else if (ql > mid) modify(id * 2 + 1, mid + 1, r, ql,qr, t);
	else {
		modify(id * 2, l, mid, ql, mid, t);
		modify(id * 2 + 1, mid + 1, r, mid + 1, qr, t);
	}
	update(id);
} 
// [ql, qr]表示查询的区间
info query(int id, int l, int r, int ql, int qr) {
	if (l == ql && r == qr) return seg[id].val;
	int mid = (l + r) / 2;
	pushdown(id);
	if (qr <= mid) return query(id * 2, l, mid, ql, qr);
	else if (ql > mid) return query(id * 2 + 1, mid + 1, r, ql,qr);
	else {
		return query(id * 2, l, mid, ql, mid) +
			query(id * 2 + 1, mid + 1, r, mid + 1, qr);
	}
}

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
	idx[tot] = u;
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

int query(int u, int v) {
	info ansu{0, 0, -1}, ansv{0, 0, -1};
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) {
			ansv = query(1, 1, n, l[top[v]], l[v]) + ansv;
			v = fa[top[v]];
		} else {
			ansu = query(1, 1, n, l[top[u]], l[u]) + ansu;
			u = fa[top[u]];
		}
	}
	if (dep[u] <= dep[v]) ansv = query(1, 1, n, l[u], l[v]) + ansv;
	else ansu = query(1, 1, n, l[v], l[u]) + ansu;
	return ansu.seg + ansv.seg + (ansu.lc != ansv.lc) + 1;
}

void modify(int u, int v, int c) {
	while (top[u] != top[v]) {
		if (dep[top[u]] > dep[top[v]]) swap(u, v);
		modify(1, 1, n, l[top[v]], l[v], c);
		v = fa[top[v]];
	}
	if (dep[u] > dep[v]) swap(u, v);
	modify(1, 1, n, l[u], l[v], c);
}

int main(){
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &w[i]);
	}
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs1(1, 0);
	dfs2(1, 1);
	build(1, 1, n);
	for (int i = 0; i < m; i++) {
		int u, v;
		static char op[10];
		scanf("%s%d%d", op, &u, &v);
		if (op[0] == 'C') {
			int c;
			scanf("%d",&c);
			modify(u, v, c);
		} else {
			printf("%d\n", query(u, v));
		}
	}
}
