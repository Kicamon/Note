#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 101000;

int n, m, w[N];
vector<int> e[N];
int l[N], r[N], idx[N];
int sz[N], hs[N], tot, top[N], dep[N], fa[N];

struct node {
	int cnt;
	int sz;
	int t;
} seg[N * 4];

// [l, r]

void settag(int id, int t) {
	if (t == 1) {
		seg[id].cnt = seg[id].sz;
	} else {
		seg[id].cnt = 0;
	}
	seg[id].t = t;
}

void pushdown(int id) {
	if (seg[id].t != -1) { // 标记非空
		settag(id * 2, seg[id].t);
		settag(id * 2 + 1, seg[id].t);
		seg[id].t = -1;
	}
}

void update(int id) {
	seg[id].cnt = seg[id * 2].cnt + seg[id * 2 + 1].cnt;
}

void build(int id, int l, int r) {
	seg[id].sz = r - l + 1;
	seg[id].t = -1;
	if (l == r) {
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

void install(int x) {
	while (x != 0) {
		modify(1, 1, n, l[top[x]], l[x], 1);
		x = fa[top[x]];
	}
}

void uninstall(int x) {
	modify(1, 1, n, l[x], r[x], 0);
}

int main(){
	scanf("%d", &n);
	for (int i = 2; i <= n; i++) {
		scanf("%d", &fa[i]);
		++fa[i];
		e[fa[i]].push_back(i);
	}
	dfs1(1, 0);
	dfs2(1, 1);
	build(1, 1, n);
	scanf("%d", &m);
	int pre = 0;
	for (int i = 0; i < m; i++) {
		int x;
		static char op[10];
		scanf("%s%d", op, &x);
		x++;
		if (op[0] == 'i') {
			install(x);
		} else {
			uninstall(x);
		}
		printf("%d\n", abs(pre - seg[1].cnt));
		pre = seg[1].cnt;
	}
}
