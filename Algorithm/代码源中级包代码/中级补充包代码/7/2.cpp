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

void answer(int x, int y) {
	for (int i = x; i <= y; i++) printf("%c", s[i]);
	puts("");
	exit(0);
}

int T, k, f[N], sz[N], len[N];
vector<int> pos[N];
vector<array<int, 3>> seg[N];

int find(int x) {
	return f[x] == x ? x : f[x] = find(f[x]);
}

int main() {
	scanf("%s", s);
	n = strlen(s);
	buildSA(s, sa, rk, ht, n);
	scanf("%d%d", &T, &k);
	if (T == 0) {
		for (int i = 0; i < n; i++) {
			seg[i].push_back({i == 0 ? 1 : ht[i] + 1, n - sa[i], 1});
		}
	} else {
		for (int i = 0; i < n; i++)
			f[i] = i, sz[i] = 1;
		for (int i = 1; i < n; i++) {
			pos[ht[i]].push_back(i);
		}
		for (int i = 0; i < n; i++)
			len[i] = n - sa[i];
		for (int l = n - 1; l >= 0; l--) {
			for (auto p : pos[l]) {
				int u = find(p - 1), v = find(p);
				if (len[u] > l)
					seg[u].push_back({l + 1, len[u], sz[u]});
				if (len[v] > l)
					seg[v].push_back({l + 1, len[v], sz[v]});
				f[v] = u;
				sz[u] += sz[v];
				len[u] = l;
			}
		}
		if (len[0] > 0) {
			seg[0].push_back({1, len[0], sz[0]});
		}
		for (int i = 0; i < n; i++) {
			reverse(seg[i].begin(), seg[i].end());
		}
	}
	for (int i = 0; i < n; i++) {
		for (auto [l, r, sz] : seg[i]) {
			if (k > (ll)(r - l + 1) * sz) {
				k -= (ll)(r - l + 1) * sz;
			} else {
				answer(sa[i], sa[i] + l + (k - 1) / sz - 1);
			}
		}
	}
	puts("-1");
}