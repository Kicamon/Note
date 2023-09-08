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
const int N = 160;
int n, m, k;
ll  d[N][N], dis[N][N];
int main() {
	scanf("%d%d%d", &n, &m, &k);
	int s = 2 * n + 1, t = 2 * n + 2, ss = 2 * n + 3, tt = 2 * n + 4;
	g.init(s, t, tt);
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			if (i != j) d[i][j] = inf;
	for (int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		d[u][v] = d[v][u] = min(d[u][v], (ll)w);
	}
	for (int k = 0; k <= n; k++) {
		for (int i = 0; i < k ;i++)
			dis[i][k] = d[i][k];
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= n; j++)
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
	}
	g.addedge(tt, ss, k, 0);
	for (int i = 1; i <= n; i++) {
		g.addedge(ss, 2 * i - 1, inf, dis[0][i]);
		g.addedge(2 * i, tt, inf, 0);
		g.addedge(s, 2 * i, 1, 0);
		g.addedge(2 * i - 1, t, 1, 0);
		for (int j = i + 1; j <= n; j++)
			g.addedge(2 * i, 2 * j - 1, inf, dis[i][j]);
	}
	auto [flow, cost] = g.solve();
	// flow != n 无解
	printf("%lld\n", cost);
}