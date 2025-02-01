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
int n, m;
int c[110][110];
int main() {
	scanf("%d%d", &n, &m);
	int s = n * m + 1;
	int t = n * m + 2;
	g.init(s, t, t);
	int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int x;
			scanf("%d", &x);
			ans += x;
			int id = i * m + j + 1;
			if ((i + j) & 1) {
				g.addedge(s, id, x);
			} else {
				g.addedge(id, t, x);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int x;
			scanf("%d", &x);
			ans += x;
			int id = i * m + j + 1;
			if ((i + j) & 1) {
				g.addedge(id, t, x);
			} else {
				g.addedge(s, id, x);
			}
		}
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &c[i][j]);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			if (i + 1 < n) {
				int id1 = i * m + j + 1;
				int id2 = (i + 1) * m + j + 1;
				ans += c[i][j] + c[i + 1][j];
				g.addedge(id1, id2, c[i][j] + c[i + 1][j],
					c[i][j] + c[i + 1][j]);
			}

			if (j + 1 < m) {
				int id1 = i * m + j + 1;
				int id2 = i * m + j + 2;
				ans += c[i][j] + c[i][j + 1];
				g.addedge(id1, id2, c[i][j] + c[i][j + 1],
					c[i][j] + c[i][j + 1]);
			}

		}
	ans -= g.dinic();
	printf("%d\n", ans);
}