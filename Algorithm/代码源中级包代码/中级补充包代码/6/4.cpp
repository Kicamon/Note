#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int M = 26, N = 100100;
struct node {
	node *son[M], *go[M], *fail, *par;
	vector<node*> t; // fail 树上的儿子
	int l, r;
	vector<pair<int,int>> q;
}pool[N], *cur = pool, *q[N], *root, *d[N];

node *newnode() {
	return cur++;
}
int t, n, Q, ans[N];
char s[N];

void build() {
	t = 0;
	q[t++] = root;
	for (int i = 0; i < t; i++) {
		node *u = q[i];
		for (int j = 0; j < M; j++) {
			if (u->son[j]) {
				u->go[j] = u->son[j];
				if (u != root) u->go[j]->fail = u->fail->go[j];
				else u->go[j]->fail = root;
				q[t++] = u->son[j];
			}
			else {
				if (u != root) u->go[j] = u->fail->go[j];
				else u->go[j] = root;
			}
		}
	}
	for (int i = 1; i < t; i++) {
		q[i]->fail->t.push_back(q[i]);
	}
	int tot = 0;
	function<void(node*)> dfs=[&](node *u) {
		u->l = ++tot;
		for (auto v : u->t) {
			dfs(v);
		}
		u->r = tot;
	};
	dfs(root);
}

template<class T>
struct BIT {
	T c[N];
	int size;
	void init(int s) {
		size = s;
		for (int i = 1; i <= s; i++) c[i] = 0;
	}
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

BIT<int> c;

void dfs(node *u) {
	c.modify(u->l, 1);
	for (auto [x, id] : u->q) {
		ans[id] = c.query(d[x]->r) - c.query(d[x]->l - 1);
	}
	for (int j = 0; j < M; j++) if (u->son[j]) {
		dfs(u->son[j]);
	}
	c.modify(u->l, -1);
}

int main() {
	scanf("%s", s);
	root = newnode();
	node *p = root;
	int l = strlen(s);
	for (int i = 0; i < l; i++) {
		if (s[i] >= 'a' && s[i] <= 'z') {
			int w = s[i] - 'a';
			if (!p->son[w]) {
				p->son[w] = newnode();
				p->son[w]->par = p;
			}
			p = p->son[w];
		} else if (s[i] == 'B') {
			p = p->par;
		} else {
			d[++n] = p;
		}
	}
	build();
	scanf("%d", &Q);
	for (int i = 0; i < Q; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		d[y]->q.push_back({x, i});
	}
	c.init(cur - pool);
	dfs(root);
	for (int i = 0; i < Q; i++) {
		printf("%d\n", ans[i]);
	}
}