#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 101000;
vector<int> e[N];

int dfn[N], low[N], idx, n, m, cnt;
bool cut[N];
stack<int> stk;
vector<int> cc[N];

void dfs(int u, int f) {
	dfn[u] = low[u] = ++idx;
	stk.push(u);

	int ch = 0;
	for (auto v : e[u]) {
		if (!dfn[v]) {
			dfs(v, u);
			ch++;
			low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u]) {
				cut[u] = 1;
				++cnt;
				cc[cnt].clear();
				cc[cnt].push_back(u);
				while (true) {
					int w = stk.top();
					cc[cnt].push_back(w);
					stk.pop();
					if (w == v) break;
				}
			}
		} else if (v != f) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (u == 1 && ch <= 1) cut[u] = 0;
}

int main() {
	int t = 0;
	while (1) {
		scanf("%d", &m);
		if (m == 0) break;
		for (int i = 1; i <= 1000; i++)
			e[i].clear();
		int n = 0;
		for (int i = 0; i < m; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			e[v].push_back(u);
			n = max(n, max(u, v));
		}
		for (int i = 1; i <= n; i++) {
			dfn[i] = low[i] = cut[i] = 0;
		}
		idx = 0; cnt = 0;
		while (!stk.empty()) stk.pop();
		for (int i = 1; i <= n; i++) if (!dfn[i])
			dfs(i, 0);
		printf("Case %d: ", ++t);
		if (cnt == 1) {
			int n = cc[1].size();
			printf("%d %d\n", 2, n * (n - 1) /2);
		} else {
			int ans1 = 0;
			ll ans2 = 1;
			for (int i = 1; i <= cnt; i++) {
				int ncut = 0;
				for (auto u : cc[i]) {
					ncut += cut[u];
				}
				if (ncut == 1) {
					ans1 += 1;
					ans2 *= (int)cc[i].size() - 1;
				}
			}
			printf("%d %lld\n", ans1, ans2);
		}
	}
}
