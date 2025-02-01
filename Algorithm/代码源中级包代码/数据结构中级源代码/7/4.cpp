#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 501000;
const int LOGN = 20;
int n, q, p[N], tot, dep[N];
vector<int> e[N];
pair<int,int> f[LOGN + 2][N * 2];
ll ans;

void dfs(int u, int par) {
	p[u] = ++tot;
	dep[u] = dep[par] + 1;
	f[0][tot] = {dep[u], u};
	for (auto v : e[u]) {
		if (v == par) continue;
		dfs(v, u);
		f[0][++tot] = {dep[u], u};
	}
}

unsigned int A, B, C;
inline unsigned int rng61() {
	A ^= A << 16;
	A ^= A >> 5;
	A ^= A << 1;
	unsigned int t = A;
	A = B;
	B = C;
	C ^= t ^ A;
	return C;
}


int main(){
	scanf("%d%d%u%u%u", &n, &q, &A, &B, &C);
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1, 0);
	for (int j = 1; j <= LOGN; j++) {
		for (int i = 1; i + (1 << j) - 1 <= tot; i++) {
			f[j][i] = min(f[j - 1][i], f[j - 1][i + (1 << (j - 1))]);
		}
	}
	for (int i = 1; i <= q; i++) {
		int l = p[rng61() % n + 1], r = p[rng61() % n + 1];
		if (l > r) swap(l, r);
		int len = 31 - __builtin_clz(r - l + 1);
		int d = min(f[len][l], f[len][r - (1 << len) + 1]).second;
		ans ^= 1ll * i * d;
	}
	printf("%lld\n", ans);
}
