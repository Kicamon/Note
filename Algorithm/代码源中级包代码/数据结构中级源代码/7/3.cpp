#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000;

int n, q, l[N], r[N], tot, a[N];
vector<int> e[N];
vector<pair<int,int>> son[N];

template<class T>
struct BIT {
	T c[N];
	int size;
	void init(int s) {
		size = s;
		for (int i = 1; i <= size; i++) c[i] = 0;
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

BIT<ll> c1;

void dfs(int u, int f) {
	l[u] = ++tot;
	for (auto v : e[u]) {
		if (v == f) continue;
		dfs(v, u);
		son[u].push_back({l[v], r[v]});
	}
	r[u] = tot;
}

int main() {
	scanf("%d%d",&n, &q);
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1, 0);
	int root = 1;
	c1.init(n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		c1.modify(l[i], a[i]);
	}
	for (int i = 1; i <= q; i++) {
		int ty;
		scanf("%d", &ty);
		if (ty == 1) {
			int x, y;
			scanf("%d%d", &x, &y);
			int d = y - a[x];
			a[x] = y;
			c1.modify(l[x], d);
		} else if (ty == 3) {
			scanf("%d", &root);
		} else {
			int x;
			scanf("%d", &x);
			if (x == root) {
				printf("%lld\n", c1.query(n));
			} else if (l[x] < l[root] && r[root] <= r[x]) {
				auto seg = *prev(upper_bound(son[x].begin(), son[x].end(),
					pair<int,int>{l[root], r[root]}));
				printf("%lld\n", c1.query(n) - (c1.query(seg.second) - 
					c1.query(seg.first - 1)));
			} else {
				printf("%lld\n", c1.query(r[x]) - c1.query(l[x] - 1));
			}
		}
	}
}