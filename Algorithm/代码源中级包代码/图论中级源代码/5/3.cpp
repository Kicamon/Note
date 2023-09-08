#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 4001000;
vector<int> e[N];

int dfn[N], low[N], ins[N], bel[N], idx, n, m, k, cnt;
stack<int> stk;
int x[N], pre[N];

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

void add(int u, int v) {
	e[u].push_back(v);
	e[v ^ 1].push_back(u ^ 1);
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	// 2 * i, 2 * i + 1
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		--u; --v;
		add(2 * u + 1, 2 * v);
	}
	int tot = n;
	for (int i = 0; i < k; i++) {
		int sz;
		scanf("%d", &sz);
		for (int j = 0; j < sz; j++) {
			scanf("%d", &x[j]);
			--x[j];
			pre[j] = tot++;
			add(2 * pre[j], 2 * x[j] + 1);
			if (j != 0) {
				add(2 * pre[j], 2 * pre[j - 1]);
				add(2 * x[j], 2 * pre[j - 1]);
			}
		}
	}
	for (int i = 0; i < 2 * tot; i++) if (dfn[i] == 0)
		dfs(i);
	for (int i = 0; i < n; i++) {
		if (bel[2 * i] == bel[2 * i + 1]) {
			puts("NIE");
			return 0;
		}
	}
	puts("TAK");
}
