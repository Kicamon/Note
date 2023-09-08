#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int V = 1010;
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
		for (int i = 1; i <= vtot; i++) head[i] = -1;
	}
};

FlowGraph<ll> g;
int n, k;
vector<array<int, 3>> used;
vector<int> prob[30];
int main() {
	scanf("%d%d", &k, &n);
	//1...k k+1...n+k
	int s = n + k + 1;
	int t = n + k + 2;
	g.init(s, t, t);
	int totx = 0;
	for (int i = 1; i <= k; i++) {
		int x;
		scanf("%d", &x);
		g.addedge(s, i, x);
		totx += x;
	}
	for (int i = 1; i <= n; i++) {
		g.addedge(i + k, t, 1);
		int c;
		scanf("%d", &c);
		for (int j = 0; j < c; j++) {
			int x;
			scanf("%d", &x);
			used.push_back({x, i, g.etot});
			g.addedge(x, i + k, 1);
		}
	}
	int tot = g.dinic();
	if (tot != totx) {
		puts("No Solution!");
		return 0;
	}
	for (auto [p, q, id] : used) {
		if (g.e[id].f == 0) {
			prob[p].push_back(q);
		}
	}
	for (int i = 1; i <= k; i++) {
		printf("%d: ", i);
		for (auto x : prob[i]) printf("%d ", x);
		puts("");
	}
}