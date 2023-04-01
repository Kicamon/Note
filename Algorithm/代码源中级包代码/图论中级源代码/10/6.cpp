#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int V = 201000;
const int E_ = 1001000;
template<typename T>
struct FlowGraph {
	int s, t, vtot;
	int head[V], etot;
	int dis[V], cur[V];
	struct edge {
		int v, nxt;
		T f;
	} e[E_ * 2];
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

const int N = 101000;
FlowGraph<int> g;

int n, m, s, t;
vector<int> e[N];
int dfn[N], low[N], ins[N], bel[N], idx, cnt;
stack<int> stk;
array<int, 3> E[N];

void dfs(int u) {
	dfn[u] = low[u] = ++idx;
	ins[u] = true;
	stk.push(u);
	for (auto v : e[u]) {
		if (!dfn[v]) dfs(v);
		if (ins[v]) low[u] = min(low[u], low[v]);
	}
	if (dfn[u] == low[u]) {
		++cnt;
		while (true) {
			int v = stk.top();
			ins[v] = false;
			bel[v] = cnt;
			stk.pop();
			if (v == u) break;
		}
	}
}

int main() {
	scanf("%d%d%d%d", &n, &m, &s, &t);
	g.init(s, t, n);
	for (int i = 0; i < m; i++) {
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		E[i] = {u, v, g.etot};
		g.addedge(u, v, c);
	}
	g.dinic();
	for (int i = 0; i < m; i++) {
		auto [u, v, id] = E[i];
		if (g.e[id].f > 0) e[u].push_back(v);
		if (g.e[id ^ 1].f > 0) e[v].push_back(u);
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) dfs(i);
	for (int i = 0; i < m; i++) {
		auto [u, v, id] = E[i];
		if (g.e[id].f != 0) {
			puts("0 0");
			continue;
		}
		printf("%d %d\n", (int)(bel[u] != bel[v]),
			(int)(bel[u] == bel[s] && bel[v] == bel[t]));
	}
	
}