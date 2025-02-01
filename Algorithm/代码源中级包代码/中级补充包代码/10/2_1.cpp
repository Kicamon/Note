#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 3010;
int n, m;
vector<int> e[N];
bitset<N> g[N];

int main() {
/*	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
	}*/
	for (1 <= u < v <= n) ans += (g[u]&g[v]).count();
	//u, v g[u][w], g[v][w]
	ans /= 3;
}
