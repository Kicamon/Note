#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int V = 20100;
const int E = 201000;
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

const ll inf = 1ll << 60;
FlowGraph<ll> g;
int n, m;
int main() {
    cin >> m >> n;
    string str;
    getline(std::cin, str);

    int s = m + n + 1, t = m + n + 2;
    g.init(s, t, t);
    ll ans = 0;

    for (int i = 1; i <= m; i++) {
        getline(cin, str);
        stringstream ss;
        ss << str;
        int x;
        ss >> x;

        g.addedge(s, i, x);
        ans += x;
        
        while (!ss.eof()) {
            ss >> x;
            g.addedge(i, x + m, inf);
        }
    }
    for (int i = 1; i <= n; i++) {
    	int x;
    	cin >> x;
    	g.addedge(i + m, t, x);
    }
    vector<int> p1, p2;
    ans -= g.dinic();
    for (int i = 1; i <= m; i++) 
    	if (g.dis[i] > 0) p1.push_back(i);
    for (int i = 1; i <= n; i++) 
    	if (g.dis[i + m] > 0) p2.push_back(i);
   	for (int i = 0; i < p1.size(); i++)
   		printf("%d ", p1[i]);
   	puts("");
   	for (int i = 0; i < p2.size(); i++)
   		printf("%d ", p2[i]);
   	puts("");
    printf("%lld\n", ans);
}