#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 101000;
template<class T>
struct BIT {
	vector<T> c;
	int size;
	void init(int s) {
		size = s + 1;
		c = vector<T>(size + 1, 0);
	}
	T query(int x) { // 1 ... x
		x += 1;
		if (x < 0) return 0;
		x = min(x, size);
		T s = 0;
		for (; x; x -= x & (-x)) {
			s += c[x];
		}
		return s;
	}

	void modify(int x, T s) { // a[x] += s
		x += 1;
		assert(x != 0);
		for (; x <= size; x += x & (-x)) {
			c[x] += s;
		}
	} 
};

BIT<int> c[2 * N];
int tot;

int n, sz[N], maxs[N], w[N], Q;
vector<int> e[N];
bool del[N];
int preans;
vector<array<int, 3>> b[N];

void solve(int u, int s) {
	int ms = s + 1, root = -1;
	function<void(int, int)> dfs1 = [&](int u, int par) {
		sz[u] = 1;
		maxs[u] = 0;
		for (auto v: e[u]) {
			if (del[v] || v == par) continue;
			dfs1(v, u);
			sz[u] += sz[v];
			maxs[u] = max(maxs[u], sz[v]);
		}
		maxs[u] = max(maxs[u], s - sz[u]);
		if (maxs[u] < ms) ms = maxs[u], root = u;
	};
	dfs1(u, -1);
	int t1 = tot++;
	int d1 = 0;
	b[root].push_back({0, t1, 0});
	for (auto v : e[root]) {
		if (del[v]) continue;
		int d2 = 0;
		int t2 = tot++;
		function<void(int, int, int)> dfs2 = [&](int u, int par, int dep) {
			d1 = max(d1, dep);
			d2 = max(d2, dep);
			b[u].push_back({dep, t1, 0});
			b[u].push_back({dep, t2, 1});
			for (auto v : e[u]) {
				if (del[v] || v == par) continue;
				dfs2(v, u, dep + 1);
			}
		};
		dfs2(v, root, 1);
		c[t2].init(d2);
	}
	c[t1].init(d1);
	del[root] = true;
	for (auto v : e[root]) {
		if (!del[v]) solve(v, sz[v]);
	}
}

void modify(int x, int v) {
	for (auto [d, id, ty] : b[x]) {
		c[id].modify(d, v);
	}
}
int query(int x, int k) {
	int ans = 0;
	for (auto [d, id, ty] : b[x]) {
		if (ty == 0) ans += c[id].query(k - d);
		else ans -= c[id].query(k - d);
	}
	return ans;
}

int main() {
	scanf("%d%d", &n, &Q);
	for (int i = 1; i <= n; i++)
		scanf("%d", &w[i]);
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	solve(1, n);
	for (int i = 1; i <= n; i++) {
		modify(i, w[i]);
	}
	for (int i = 0; i < Q; i++) {
		int op, x, y;
		scanf("%d%d%d", &op, &x, &y);
		x ^= preans;
		y ^= preans;
		if (op == 1) modify(x, y - w[x]), w[x] = y;
		else {
			preans = query(x, y);
			printf("%d\n", preans);
		}
	}
}