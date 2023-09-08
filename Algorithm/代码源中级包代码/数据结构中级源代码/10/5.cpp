#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 301000;
const int LOGN = 18;

int n;
vector<int> e[N];
int sz[N], hs[N], fa[N], tot;
int go[N][20];
ll ans;

// 第一遍DFS，子树大小，重儿子，父亲，深度
void dfs1(int u,int f) {
	sz[u] = 1;
	hs[u] = 0;
	fa[u] = f;
	for (auto v : e[u]) {
		if (v == f) continue;
		dfs1(v, u);
		sz[u] += sz[v];
		if (hs[u] == 0 || sz[v] > sz[hs[u]])
			hs[u] = v;
	}
	go[u][0] = hs[u];
	for (int j = 1; j <= LOGN; j++) go[u][j] = go[go[u][j - 1]][j - 1];
}

void changeroot(int u, int v) {
	sz[u] = n - sz[v];
	sz[v] = n;
	fa[u] = v;
	fa[v] = 0;
	auto updhs = [&](int u) {
		go[u][0] = hs[u];
		for (int j = 1; j <= LOGN; j++)
			go[u][j] = go[go[u][j - 1]][j - 1];
	};
	if (hs[u] == v) {
		hs[u] = 0;
		for (auto v : e[u]) if (v != fa[u]) {
			if (hs[u] == 0 || sz[v] > sz[hs[u]])
				hs[u] = v;
		}
		updhs(u);
	}
	if (sz[u] >= sz[hs[v]]) {
		hs[v] = u;
		updhs(v);
	}
}
int query(int v) {
	int t = (sz[v] + 1) / 2;
	int w = v, ans = 0;
	for (int j = LOGN; j >= 0; j--) {
		if (sz[go[w][j]] >= t) w = go[w][j];
	}
	if (max(sz[hs[w]], sz[v] - sz[w]) <= sz[v] / 2) ans += w;
	if (v != w) {
		w = fa[w];
		if (max(sz[hs[w]], sz[v] - sz[w]) <= sz[v] / 2) ans += w;
	}
	return ans;
}

void dfs2(int u, int f) {
	for (auto v : e[u]) {
		if (v == f) continue;
		ans += query(v);
		changeroot(u, v);
		ans += query(u);
		dfs2(v, u);
		changeroot(v, u);
	}
}

void solve(int T) {
	scanf("%d" ,&n);
	for (int i = 1; i <= n; i++) {
		e[i].clear();
	}
	for (int i = 1; i < n; i++)	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	ans = 0;
	dfs1(1, 0);
	dfs2(1, 0);
	printf("%lld\n", ans);
}

int main(){
	int tc;
	scanf("%d", &tc);
	for (int T = 0; T < tc; T++) {
		solve(T);
	}
}
