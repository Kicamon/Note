#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 501000;
char s[N];
int sa[N], rk[N], ht[N], n;
// 0-based sa 表示第i大的为哪个，rk 表示第i个后缀第几大
// ht表示 lcp(sa[i], sa[i-1])
void buildSA(char *s, int *sa, int *rk, int *ht, int n, int m = 128) {
	static int x[N], y[N], c[N];
	s[n] = 0;
	for (int i = 0; i < m; i++) c[i] = 0;
	for (int i = 0; i < n; i++) c[x[i] = s[i]]++;
	for (int i = 1; i < m; i++) c[i] += c[i - 1];
	for (int i = n - 1; i >= 0; i--) sa[--c[x[i]]] = i;
	for (int k = 1; k < n; k <<= 1) {
		int p=0;
		for (int i = n - 1; i >= n - k; i--) y[p++] = i;
		for (int i = 0; i < n; i++) if (sa[i] >= k) y[p++] = sa[i] - k;
		for (int i = 0; i < m; i++) c[i] = 0;
		for (int i = 0; i < n; i++) c[x[y[i]]]++;
		for (int i = 1; i < m; i++) c[i] += c[i - 1];
		for (int i = n - 1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
		swap(x, y);
		p = 1; x[sa[0]] = 0; y[n] = -1;
		for (int i = 1; i < n; i++) {
			if (y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k])
				x[sa[i]] = p - 1;
			else
				x[sa[i]] = p++;
		}
		if (p == n) break;
		m = p;
	}
	for (int i = 0; i < n; i++) rk[sa[i]] = i;
	int k = 0;
	for (int i = 0; i < n; i++) {
		k = max(k - 1, 0);
		if (rk[i] == 0) continue;
		int j = sa[rk[i] - 1];
		while (s[i + k] == s[j + k]) k++;
		ht[rk[i]] = k;
	}
}

int f[N], sz[N], mx[N], mn[N], a[N];
ll ans1, ans2, ret[N][2];
vector<int> pos[N];

int find(int x) {
	return f[x] == x ? x : f[x] = find(f[x]);
}

int main() {
	scanf("%d", &n);
	scanf("%s", s);
	n = strlen(s);
	buildSA(s, sa, rk, ht, n);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	for (int i = 0; i < n; i++) {
		f[i] = i, sz[i] = 1;
		mx[i] = a[sa[i]], mn[i] = a[sa[i]];
	}
	ans1 = 0;
	ans2 = -(1ll << 60);
	for (int i = 1; i < n; i++) {
		pos[ht[i]].push_back(i);
	}
	for (int l = n - 1; l >= 0; l--) {
		for (auto p : pos[l]) {
			int u = find(p - 1), v = find(p);
			f[v] = u;
			ans1 += (ll)sz[u] * sz[v];
			ans2 = max(ans2, (ll)mx[u] * mx[v]);
			ans2 = max(ans2, (ll)mn[u] * mn[v]);
			mx[u] = max(mx[u], mx[v]);
			mn[u] = min(mn[u], mn[v]);
			sz[u] += sz[v];
		}
		ret[l][0] = ans1;
		if (ans1) ret[l][1] = ans2;
	}
	for (int l = 0; l < n; l++) {
		printf("%lld %lld\n",ret[l][0], ret[l][1]);
	}
}