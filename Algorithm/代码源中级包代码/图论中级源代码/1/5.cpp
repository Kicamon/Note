#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 301000;
vector<int> e[N];

int n, R, C, x[N], y[N], ty[N], cnt;
map<int, vector<int>> r, c;
map<int, int> rid, cid;
map<pair<int, int>, int> id;

int dfn[N], low[N], ins[N], bel[N], idx;
stack<int> stk;
int dp[N], ans;

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
		int sz = 0;
		dp[cnt] = 0;
		while (true) {
			int v = stk.top();
			ins[v] = false;
			bel[v] = cnt;
			sz += (v <= n);
			for (int w : e[v]) if (bel[w] != cnt && bel[w] != 0) {
				dp[cnt] = max(dp[cnt], dp[bel[w]]);
			}
			stk.pop();
			if (v == u) break;
		}
		dp[cnt] += sz;
		ans = max(ans, dp[cnt]);
	}
}

int main() {
	scanf("%d%d%d", &n, &R, &C);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d%d", x + i, y + i, ty + i);
		id[make_pair(x[i], y[i])] = i;
		r[x[i]].push_back(i);
		c[y[i]].push_back(i);
	}
	int tot = n;
	for (int i = 1; i <= n; i++) {
		if (ty[i] == 1) {
			if (!rid.count(x[i])) {
				rid[x[i]] = ++tot;
				for (auto id : r[x[i]]) e[tot].push_back(id);
			}
			e[i].push_back(rid[x[i]]);
		} else if (ty[i] == 2) {
			if (!cid.count(y[i])) {
				cid[y[i]] = ++tot;
				for (auto id : c[y[i]]) e[tot].push_back(id);
			}
			e[i].push_back(cid[y[i]]);
		} else if (ty[i] == 3) {
			for (int dx = -1; dx <= 1; dx++)
				for (int dy = -1; dy <= 1; dy++) {
					if (dx == 0 && dy == 0) continue;
					if (!id.count(make_pair(x[i] + dx, y[i] + dy))) continue;
					e[i].push_back(id[make_pair(x[i] + dx, y[i] + dy)]);
				}
		}
	}
	for (int i = 1; i <= tot; i++) 
		if (!dfn[i]) dfs(i);
	printf("%d\n", ans);
}
