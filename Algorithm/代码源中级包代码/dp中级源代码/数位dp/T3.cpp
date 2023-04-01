#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf = 1ll<<60;

vector<pair<int,int>> item[40];
ll f[2010], g[2010];
int n, W;

void solve() {
	int s = 0;
	for (int i = 0; i <= 30; i++) item[i].clear();
	for (int i = 0; i < n; i++) {
		int w, v;
		scanf("%d%d",&w, &v);
		int lev = __builtin_ctz(w);
		w >>= lev;
		item[lev].push_back({w, v});
		s += w;
	}
	for (int i = 0; i <= s; i++) f[i] = -inf;
	f[0] = 0; // >= 2^31的背包
	for (int i = 30; i >= 0; i--) {
		// i + 1 -> i
		for (int i = 0; i <= s; i++) g[i] = f[i], f[i] = -inf;
		int d = (W >> i) & 1;
		for (int i = 0; i <= s; i++) {
			f[min(2 * i + d, s)] = max(f[min(2 * i + d, s)], g[i]);
		}
		for (int i = s - 1; i >= 0; i--)
			f[i] = max(f[i], f[i + 1]);
		for (auto p : item[i]) {
			for (int i = p.first; i <= s; i++) 
				f[i - p.first] = max(f[i - p.first], f[i] + p.second);
		}
	}
	printf("%lld\n", f[0]);
}

int main() {
	while (true) {
		scanf("%d%d",&n,&W);
		if (n == -1 && W == -1)
			break;
		solve();
	}
}