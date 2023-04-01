#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int V = 20100;
const int E = 201000;

template<typename T>
struct MinCostGraph {
	int s, t, vtot;
	int head[V], etot;
	T dis[V], flow, cost, pf[V];
	int pre[V];
	bool vis[V];

	struct edge {
		int v, nxt;
		T f, c;
	} e[E * 2];
	void addedge(int u,int v, T f, T c, T f2 = 0){
		e[etot]= {v, head[u], f, c}; head[u] = etot++;
		e[etot]= {u, head[v], f2, -c}; head[v] = etot++;
	}

	bool spfa() {
		T inf = numeric_limits<T>::max() / 2;
		for (int i = 1; i <= vtot; i++) {
			dis[i] = inf;
			vis[i] = false;
			pre[i] = -1;
			pf[i] = inf;
		}
		dis[s] = 0;
		vis[s] = true;
		queue<int> q;
		q.push(s);
		while (!q.empty()) {
			int u = q.front();
			for (int i = head[u]; ~i; i = e[i].nxt) {
				int v = e[i].v;
				if (e[i].f && dis[v] > dis[u] + e[i].c) {
					dis[v] = dis[u] + e[i].c;
					pre[v] = i;
					pf[v] = min(pf[u], e[i].f);
					if (!vis[v]) {
						vis[v] = 1;
						q.push(v);
					}
				}
			}
			q.pop();
			vis[u] = false;
		}
		return dis[t] != inf;
	}

	void augment() {
		int u = t;
		T f = pf[t];
		flow += f;
		cost += f * dis[t];
		while (~pre[u]) {
			e[pre[u]].f -= f;
			e[pre[u] ^ 1].f += f;
			u = e[pre[u] ^ 1].v;
		}
	}

	pair<T, T> solve() {
		flow = 0;
		cost = 0;
		while (spfa()) augment();
		return {flow, cost};
	}
	void init(int s_, int t_, int vtot_) {
		s = s_;
		t = t_;
		vtot = vtot_;
		etot = 0;
		for (int i = 1; i <= vtot; i++) head[i] = -1;
	}
};

MinCostGraph<ll> g;
ll inf = 1ll << 30;
int n, c0, d1, c1, d2, c2;
ll sr = 0;
int main() {
	scanf("%d%d%d%d%d%d", &n, &c0, &d1, &c1, &d2, &c2);
	int s = 2 * n + 1, t = 2 * n + 2, ss = 2 * n + 3;
	g.init(s, t, ss);
	for (int i = 1; i <= n; i++) {
		int r;
		scanf("%d", &r);
		g.addedge(ss, 2 * i - 1, inf, c0);
		g.addedge(s, 2 * i, r, 0);
		g.addedge(2 * i - 1, t, r, 0);
		if (i + 1 <= n) {
			g.addedge(2 * i, 2 * (i + 1), inf, 0);
		} else {
			g.addedge(2 * i, ss, inf ,0);
		}
		if (i + d1 <= n) {
			g.addedge(2 * i, 2 * (i + d1) - 1, inf, c1);
		}
		if (i + d2 <= n) {
			g.addedge(2 * i, 2 * (i + d2) - 1, inf, c2);
		}
	}
	auto [flow, cost] = g.solve();
	printf("%lld\n", cost);
}