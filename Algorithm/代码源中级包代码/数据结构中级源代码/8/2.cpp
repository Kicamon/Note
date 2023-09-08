#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000;

int n, q, f[N], ans[N], belong[N];
array<int, 3> E[N];
array<int, 2> Q[N];
vector<int> vec[N];
vector<pair<int,int>> que[N];

int find(int x) {
	return f[x] == x? x : f[x] = find(f[x]);
}

int main() {
	scanf("%d%d",&n, &q);
	for (int i = 1; i < n; i++) {
		scanf("%d%d%d", &E[i][1], &E[i][2], &E[i][0]);
	}
	sort(E + 1, E + n);
	reverse(E + 1, E + n);
	for (int i = 1; i <= n; i++) {
		vec[i].push_back(i);
		belong[i] = i;
		f[i] = i;
	}
	for (int i = 1; i <= q; i++) {
		scanf("%d%d", &Q[i][0], &Q[i][1]);
		que[Q[i][0]].emplace_back(i, Q[i][1]);
		que[Q[i][1]].emplace_back(i, Q[i][0]);
	}
	for (int i = 1; i < n; i++) {
		int u = find(E[i][1]), v = find(E[i][2]);
		if (vec[u].size() > vec[v].size()) {
			swap(u, v);
		}
		for (auto [id, w] : que[u]) {
			if (ans[id] != 0) continue;
			if (belong[w] == v) ans[id] = E[i][0];
			else que[v].emplace_back(id, w);
		}
		for (auto w : vec[u]) {
			vec[v].push_back(w);
			belong[w] = v;
		}
		que[u].clear();
		vec[u].clear();
		f[u] = v;
	}
	for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
}