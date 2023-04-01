#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int V = 201000;
const int E = 1001000;
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
		for (int i = 1; i <= vtot; i++) head[i] = -1;
	}
};

FlowGraph<int> g;
char p[110][110];
int n, m, a, b, _;
int main() {
	for (scanf("%d",&_); _; _--) {
		scanf("%d%d%d%d", &n, &m, &a, &b);
		int s = n * m * 2 + 1;
		int t = n * m * 2 + 2;
		g.init(s, t, t);
		for (int i = 0; i < n; i++) {
			scanf("%s", p[i]);
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (i + 1 < n && p[i][j] == '0' && p[i + 1][j] == '0') {
					g.addedge(i * m + j + 1, (i + 1) * m + j + 1, 1, 1);
				}
				if (j + 1 < m && p[i][j] == '0' && p[i][j + 1] == '0') {
					g.addedge(i * m + j + 1 + n * m, i * m + j + 2 + n * m, 1, 1);
				}
				g.addedge(i * m + j + 1, i * m + j + 1 + n * m, 1, 1);				
			}
		}
		for (int i = 0; i < a; i++) {
			int x;
			scanf("%d", &x);
			g.addedge(s, x, 1);
		}
		for (int i = 0; i < b; i++) {
			int x;
			scanf("%d", &x);
			g.addedge((n - 1) * m + x, t, 1);
		}
		int d = g.dinic();
		puts(d == a ? "Yes" : "No");
	}
}