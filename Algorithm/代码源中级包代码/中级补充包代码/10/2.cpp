#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 50010;
int n, m;
vector<int> e[N];
bitset<N> f[N];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
	}
	for (int u = n; u >= 1; u--) {
		f[u][u] = 1;
		for (auto v : e[u]) f[u] |= f[v];
	}
	for (int i = 1; i <= n; i++) {
		printf("%d\n", f[i].count());
	}
}