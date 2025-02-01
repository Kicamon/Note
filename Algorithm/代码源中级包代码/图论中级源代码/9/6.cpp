#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// R >= L, 左边完全匹配
// 最小权完备匹配

template<class T>
pair<T, vector<int>> hungarian(const vector<vector<T>> &a) {
	if (a.empty()) return {0, {}};
	int n = a.size() + 1, m = a[0].size() + 1;
	vector<T> u(n), v(m); // 顶标
	vector<int> p(m), ans(n - 1);
	for (int i = 1; i < n; i++) {
		p[0] = i;
		int j0 = 0;
		vector<T> dist(m, numeric_limits<T>::max());
		vector<int> pre(m, -1);
		vector<bool> done(m + 1);
		do { // dijkstra
			done[j0] = true;
			int i0 = p[j0], j1;
			T delta = numeric_limits<T>::max();
			for (int j = 1; j < m; j++) if (!done[j]) {
				auto cur = a[i0 - 1][j - 1] - u[i0] - v[j];
				if (cur < dist[j]) dist[j] = cur, pre[j] = j0;
				if (dist[j] < delta) delta = dist[j], j1 = j;
			}
			for (int j = 0; j < m; j++) {
				if (done[j]) u[p[j]] += delta, v[j] -= delta;
				else dist[j] -= delta;
			}
			j0 = j1;
		} while (p[j0]);
		while (j0) { // update alternating path
			int j1 = pre[j0];
			p[j0] = p[j1], j0 = j1;
		}
	}
	for (int j = 1; j < m; j++) {
		if (p[j]) ans[p[j] - 1] = j - 1;
	}
	return {-v[0], ans}; // min cost
}

int L, R, m;
int main() {
	scanf("%d%d%d", &L, &R, &m);
	R = max(L, R);
	auto a = vector<vector<ll>>(L, vector<ll>(R, 0));
	for (int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		--u; --v;
		a[u][v] = -w;
	}
	auto [val, ans] = hungarian(a);
	printf("%lld\n", -val);
	for (int i = 0; i < L; i++) {
		if (a[i][ans[i]] >= 0) ans[i] = -1;
		printf("%d%c", ans[i] + 1, " \n"[i == L - 1]);
	}
}