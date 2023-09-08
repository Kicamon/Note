#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
mt19937 mrand(random_device{}()); 

const int N = 100100;
vector<int> e[N];

int dfn[N], low[N], ins[N], bel[N], idx, n, m, d, cnt;
stack<int> stk;
vector<array<int, 4>> cc;
char ans[N], s[N];

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

bool check() {
	for (int i = 0 ; i < 2 * n; i++) {
		e[i].clear();
		dfn[i] = 0;
	}
	idx = cnt = 0;
	auto getid = [&](int x, int y) {
		if (s[x] == 'a' + y) return -1;
		if (s[x] == 'a' + (y + 1) % 3) return 2 * x + 0;
		if (s[x] == 'a' + (y + 2) % 3) return 2 * x + 1;
		assert(0);
		return -1;
	};
	for (int i = 0; i < m; i++) {
		int f1 = getid(cc[i][0], cc[i][1]);
		int f2 = getid(cc[i][2], cc[i][3]);
		if (f1 != -1 && f2 != -1) {
			e[f1].push_back(f2);
			e[f2 ^ 1].push_back(f1 ^ 1);
		} else if (f1 != -1 && f2 == -1) {
			e[f1].push_back(f1 ^ 1);
		}
	}
	for (int i = 0; i < 2 * n; i++) if (dfn[i] == 0)
		dfs(i);
	for (int i = 0; i < n; i++) {
		if (bel[2 * i] == bel[2 * i + 1]) {
			return false;
		}
	}
	for (int i = 0; i < n; i++) {
		if (bel[2 * i] < bel[2 * i + 1]) 
			ans[i] = (s[i] - 'a' + 2) % 3 + 'A';
		else 
			ans[i] = (s[i] - 'a' + 1) % 3 + 'A';
	}
	puts(ans);
	return true;
}

int main() {
	scanf("%d%d", &n, &d);
	scanf("%s", s);
	vector<int> X;
	for (int i = 0; i < n; i++) if (s[i] == 'x') {
		X.push_back(i);
	}
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		char ty1[2], ty2[2];
		int u, v;
		scanf("%d%s%d%s", &u, ty1, &v, ty2);
		--u; --v;
		cc.push_back({u, ty1[0] - 'A', v, ty2[0] - 'A'});
	}
	while (clock() <= 1.9 * CLOCKS_PER_SEC) {
		for (int i = 0; i < d; i++)
			s[X[i]] = "abc"[mrand() % 3];
		if (check()) {
			return 0;
		}
	}
	puts("-1");
}
