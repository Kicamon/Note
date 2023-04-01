#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000;

int n, q, l[N], r[N], tot, a[N];
vector<int> e[N];

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

BIT<ll> c1, c2;

void dfs(int u, int f) {
	l[u] = ++tot;
	for (auto v : e[u]) {
		if (v == f) continue;
		dfs(v, u);
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
	c1.init(n);
	c2.init(n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		c1.modify(l[i], a[i]);
		c2.modify(l[i], a[i]);
		c2.modify(r[i] + 1, -a[i]);
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
			c2.modify(l[x], d);
			c2.modify(r[x] + 1, -d);
		} else {
			int x;
			scanf("%d", &x);
			printf("%lld %lld\n", c1.query(r[x]) - c1.query(l[x] - 1), c2.query(l[x]));
		}
	}
}