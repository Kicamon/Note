#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int B = 60;

struct linear_basis {
	ll num[B + 1];
	bool insert(ll x) {
		for (int i = B - 1; i >= 0; i--) {
			if (x & (1ll << i)) {
				if (num[i] == 0) { num[i] = x; return true; }
				x ^= num[i];
			}
		}
		return false;
	}
	ll querymin(ll x) {
		for (int i = B - 1; i >= 0; i--) {
			x = min(x, x ^ num[i]);
		}
		return x;
	}
	ll querymax(ll x) {
		for (int i = B - 1; i >= 0; i--) {
			x = max(x, x ^ num[i]);
		}
		return x;
	}
}T;

const int N = 50100;
int n, m, vis[N];
vector<pair<int, ll>> e[N];
ll dis[N];
void dfs(int u) {
	vis[u] = 1;
	for (auto [v, w]: e[u]) {
		if (!vis[v]) {
			dis[v] = dis[u] ^ w;
			dfs(v);
		} else {
			T.insert(dis[u] ^ dis[v] ^ w);
		}
	}
}
int main() {
	scanf("%d%d",&n, &m);
	for (int i = 0; i < m; i++) {
		int u, v;
		ll w;
		scanf("%d%d%lld", &u, &v, &w);
		e[u].push_back(make_pair(v, w));
		e[v].push_back(make_pair(u, w));
	}
	dfs(1);
	printf("%lld\n", T.querymax(dis[n]));
}