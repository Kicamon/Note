#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000;
const int M = 500;

int n, m, q, big[N], col[N], ans[N];
vector<int> e[N], bige[N];

int main() {
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for (int i = 1; i <= n; i++)
		big[i] = e[i].size() >= M;
	for (int u = 1; u <= n; u++)
		for (auto v : e[u]) if (big[v])
			bige[u].push_back(v);
	for (int i = 0; i < q; i++) {
		int ty, x;
		scanf("%d%d", &ty, &x);
		if (ty == 1) {
			col[x] ^= 1;
			for (auto y : bige[x]) {
				if (col[x]) ans[y]++;
				else ans[y]--;
			}
		} else {
			if (big[x]) printf("%d\n", ans[x]);
			else {
				int cnt = 0;
				for (auto y : e[x]) cnt += col[y];
				printf("%d\n", cnt);
			}
		}
	}
}