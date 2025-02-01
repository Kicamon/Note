#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 101000;

int n;
vector<int> e[N];
int l[N], r[N], id[N], sz[N], hs[N], tot, a[N];
ll ans;

int cnt[(1<<20) + 10][17][2];

void dfs_init(int u,int f) {
	l[u] = ++tot;
	id[tot] = u;
	sz[u] = 1;
	hs[u] = -1;
	for (auto v : e[u]) {
		if (v == f) continue;
		dfs_init(v, u);
		sz[u] += sz[v];
		if (hs[u] == -1 || sz[v] > sz[hs[u]])
			hs[u] = v;
	}
	r[u] = tot;
}

const int M = 16;
void dfs_solve(int u, int f, bool keep) {
	for (auto v : e[u]) {
		if (v != f && v != hs[u]) {
			dfs_solve(v, u, false);
		}
	}
	if (hs[u] != -1) {
		dfs_solve(hs[u], u, true);
	}

	auto add = [&](int x) {
		for (int i = 0; i <= M; i++) {
			cnt[a[x]][i][(x >> i) & 1]++;
		}
	};

	auto del = [&](int x) {
		for (int i = 0; i <= M; i++) {
			cnt[a[x]][i][(x >> i) & 1]--;
		}
	};

	auto query = [&](int x, int v) {
		for (int i = 0; i <= M; i++)
			ans += cnt[x][i][((~v) >> i) & 1] * (1ll << i);
	};

	for (auto v : e[u]) {
		if (v != f && v != hs[u]) {  // v 是轻儿子
			for (int x = l[v]; x <= r[v]; x++) {
				query(a[id[x]] ^ a[u], id[x]);
			}
			for (int x = l[v]; x <= r[v]; x++) 
				add(id[x]);
		}
	}
	add(u);
	if (!keep) {
		for (int x = l[u]; x <= r[u]; x++) {
			del(id[x]);
		}
	}
}

int main(){
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs_init(1, 0);
	dfs_solve(1, 0, false);
	printf("%lld\n" ,ans);
}
