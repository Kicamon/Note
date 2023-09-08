#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 101000;
const ll inf = 1ll<<60;

vector<int> e[N];

int n, a[N], t[N];

ll f[N], h[N];

void dfs(int u,int par) {
	ll s = 0;
	int ma = 0;
	for (auto v : e[u]) if (v != par) {
		dfs(v, u);
		s += f[v];
		ma = max(ma, a[v]);
	}

	f[u] = s + ma;
	pair<ll, int> ma1(-inf, 0), ma2(-inf, 0);

	for (auto v : e[u]) if (v != par && t[v] == 3) {
		pair<ll, int> ma3(a[v], v);
		if (ma2 < ma3) ma2 = ma3;
		if (ma1 < ma2) swap(ma1, ma2);
	}
	for (auto v: e[u]) if (v != par) {
		ll tmp = s + h[v] - f[v];
		if (v == ma1.second) tmp += ma2.first;
		else tmp += ma1.first;
		f[u] = max(f[u], tmp);
	}
	h[u] = s + a[u];
}


void solve() {
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) {
		e[i].clear();
	}
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++)
		scanf("%d", &t[i]);
	for (int i = 2; i <= n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1, 0);
	printf("%lld\n", f[1] + a[1]);
}

int main() {
	int tc;
	for (scanf("%d",&tc); tc; tc--) {
		solve();
	}
}