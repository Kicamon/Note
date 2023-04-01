#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int V = 200100;
const int E = 2001000;
template<typename T>
struct FlowGraph {
	int s, t, vtot;
	int head[V], etot;
	int dis[V], cur[V];
	struct edge {
		int v, nxt;
		T f;
	} e[E * 2];
	void addedge(int u,int v, T f, T f2 = 0){
		e[etot]= {v, head[u], f}; head[u] = etot++;
		e[etot]= {u, head[v], f2}; head[v] = etot++;
	}

	bool bfs() {
		for (int i = 1; i <= vtot; i++) {
			dis[i] = 0;
			cur[i] = head[i];
		}
		queue<int> q;
		q.push(s); dis[s] = 1;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int i = head[u]; ~i; i = e[i].nxt) {
				if (e[i].f && !dis[e[i].v]) {
					int v = e[i].v;
					dis[v] = dis[u] + 1;
					if (v == t) return true;
					q.push(v);
				}
			}
		}
		return false;
	}

	T dfs(int u, T m) {
		if (u == t) return m;
		T flow = 0;
		for (int i = cur[u]; ~i; cur[u] = i = e[i].nxt)
			if (e[i].f && dis[e[i].v] == dis[u] + 1) {
				T f = dfs(e[i].v, min(m, e[i].f));
				e[i].f -= f;
				e[i ^ 1].f += f;
				m -= f;
				flow += f;
				if (!m) break;
			}
		if (!flow) dis[u] = -1;
		return flow;
	}
	T dinic(){
		T flow=0;
		while (bfs()) flow += dfs(s, numeric_limits<T>::max());
		return flow;
	}
	void init(int s_, int t_, int vtot_) {
		s = s_;
		t = t_;
		vtot = vtot_;
		etot = 0;
		memset(head, -1, sizeof(head));
		// for (int i = 1; i <= vtot; i++) head[i] = -1;
	}
};

const ll inf = 1ll << 60;
FlowGraph<ll> g;
int n, m, id[110][110];
int main() {
	scanf("%d%d", &n, &m);
	int s = 1, t = 2, tot = 2;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			id[i][j] = ++tot;
		}
	}
	ll ans = 0;
	g.init(1, 2, 0);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int val;
			scanf("%d", &val);
			ans += val;
			g.addedge(s, id[i][j], val);
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int val;
			scanf("%d", &val);
			ans += val;
			g.addedge(id[i][j], t, val);
		}
	}

	for (int i = 1; i <= n - 1; i++) {
		for (int j = 1; j <= m; j++) {
			int val;
			scanf("%d", &val);
			ans += val;
			int x = ++tot;
			g.addedge(s, x, val);
			g.addedge(x, id[i][j], inf);
			g.addedge(x, id[i + 1][j], inf);
		}
	}

	for (int i = 1; i <= n - 1; i++) {
		for (int j = 1; j <= m; j++) {
			int val;
			scanf("%d", &val);
			ans += val;
			int x = ++tot;
			g.addedge(x, t, val);
			g.addedge(id[i][j], x, inf);
			g.addedge(id[i + 1][j], x, inf);
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m - 1; j++) {
			int val;
			scanf("%d", &val);
			ans += val;
			int x = ++tot;
			g.addedge(s, x, val);
			g.addedge(x, id[i][j], inf);
			g.addedge(x, id[i][j + 1], inf);
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m - 1; j++) {
			int val;
			scanf("%d", &val);
			ans += val;
			int x = ++tot;
			g.addedge(x, t, val);
			g.addedge(id[i][j], x, inf);
			g.addedge(id[i][j + 1], x, inf);
		}
	}
	g.vtot = tot;

	printf("%lld\n", ans - g.dinic());
}