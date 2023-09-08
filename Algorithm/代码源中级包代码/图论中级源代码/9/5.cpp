#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 8100;

int n, m;
vector<int> e[N];
int dfn[N], low[N], ins[N], bel[N], idx, cnt;
stack<int> stk;

string s;
char ss[10];
map<string, int> name;

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
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%s", ss);
		s = ss;
		name[s] = 2 * i - 1;
		scanf("%s", ss);
		s = ss;
		name[s] = 2 * i;
		e[2 * i - 1].push_back(2 * i);
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		scanf("%s", ss);
		s = ss;
		int u = name[s];
		scanf("%s", ss);
		s = ss;
		int v = name[s];
		e[v].push_back(u);
	}
	for (int i = 1; i <= 2 * n; i++)
		if (!dfn[i]) dfs(i);
	for (int i = 1; i <= n; i++)
		if (bel[2 * i - 1] == bel[2 * i]) {
			puts("Unsafe");
		} else {
			puts("Safe");
		}
}