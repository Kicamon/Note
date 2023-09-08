#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000;

int n, q;
vector<int> e[N];
int l[N], r[N], idx[N];
int sz[N], hs[N], tot, top[N], dep[N], fa[N];

template<class T>
struct BIT {
	T c[N];
	int size;
	void resize(int s) { size = s;}
	T query(int x) { // 1 ... x
		assert(x <= size);
		T s = 0;
		for (; x; x -= x & (-x)) {
			s += c[x];
		}
		return s;
	}

	void modify(int x, T s) { // a[x] += s
		assert(x != 0);
		for (; x <= size; x += x & (-x)) {
			c[x] += s;
		}
	} 
};

BIT<uint> c1, c2;   // c1 d[i] c2 i*d[i]

void add(int l, int r, uint d) {
	c1.modify(l, d);
	c1.modify(r + 1, -d);
	c2.modify(l, l * d);
	c2.modify(r + 1, (r + 1) * (-d));
}
uint querysum(int l, int r) {
	return (r + 1) * c1.query(r) - c2.query(r) - 
		(l * c1.query(l - 1) - c2.query(l - 1));
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

int t;
array<int, 2> seg[1010];
void query(int u, int v) {
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) {
			seg[t++] = {l[top[v]], l[v]};
			v = fa[top[v]];
		} else {
			seg[t++] = {l[top[u]], l[u]};
			u = fa[top[u]];
		}
	}
	if (dep[u] <= dep[v]) seg[t++] = {l[u], l[v]};
	else seg[t++] = {l[v], l[u]}; 
}

uint query() {
	sort(seg, seg + t);
	uint ans = 0;
	int l = seg[0][0], r = seg[0][1];
	for (int i = 1; i < t; i++) {
		if (seg[i][0] <= r + 1) {
			r = max(r, seg[i][1]);
		} else {
			ans += querysum(l, r);
			l = seg[i][0];
			r = seg[i][1];
		}
	}
	ans += querysum(l, r);
	return ans;
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
	c1.resize(n);
	c2.resize(n);
	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		int op;
		scanf("%d", &op);
		if (op == 0) {
			int u, d;
			scanf("%d%d", &u, &d);
			add(l[u], r[u], d);
		} else {
			int k;
			scanf("%d", &k);
			t = 0;
			for (int i = 0; i < k; i++) {
				int u, v;
				scanf("%d%d", &u, &v);
				query(u, v);
			}
			uint ans = query();
			printf("%u\n", ans % (1u << 31));
		}
	}
}
