#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int V = 20100;
const int E = 101000;
template<typename T>
struct FlowGraph {
	int s, t, vtot;
	int head[V], etot;
	int dis[V], cur[V];
	struct edge {
		int v, nxt;
		T f;
	} e[E * 2];
	void addedge(int u,int v, T f){
		e[etot]= {v, head[u], f}; head[u] = etot++;
		e[etot]= {u, head[v], 0}; head[v] = etot++;
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
		for (int i = 1; i <= vtot; i++) head[i] = -1;
	}
};

FlowGraph<ll> g;
int n, m;
int p[V][2];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &p[i][0], &p[i][1]);
	}
	int l = 0, r = m;
	auto check = [&](int x) {
		int s = n + m + 1;
		int t = n + m + 2;
		g.init(s, t, t);
		for (int i = 1; i <= m; i++) {
			g.addedge(s, i, 1);
			g.addedge(i, p[i][0] + m, 1);
			g.addedge(i, p[i][1] + m, 1);
		}
		for (int i = 1; i <= n; i++)
			g.addedge(i + m, t, x);
		return g.dinic() == m;
	};
	while (l + 1 < r) {
		int md = (l + r) / 2;
		if (check(md)) r = md;
		else l = md;
	}
	printf("%d\n", r);
}