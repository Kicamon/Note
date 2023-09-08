#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1000000007;
const int N = 510;

int n, k, g[N][N], f[N][N], h[N][N];
char s[N];

bool match(int p, char x) {
	return s[p] == '?' || s[p] == x;
}

void add(int &a, int b) {
	a += b;
	if (a >= mod) a -= mod;
}

int main() {
	scanf("%d%d", &n, &k);
	scanf("%s", s + 1);
	for (int d = 0 ; d <= n - 1; d++) {
		for (int l = 1; l + d <= n; l++) {
			int r = l + d;
			// g[l][r] l r必须为匹配括号 Case 1, 3
			if (match(l, '(') && match(r, ')') && l != r) {
				if (r == l + 1) { // ()
					add(g[l][r], 1);
				} else if (r - l - 1 <=k) {   // (S)
					bool can = true;
					for (int i = l + 1; i <= r - 1; i++)
						if (!match(i, '*')) {
							can = false;
							break;
						}
					if (can) add(g[l][r], 1);
				}
				// (A)
				add(g[l][r], f[l + 1][r - 1]);
				// (SA)     [l + 1, r - 1] SA
				add(g[l][r], h[l + 1][r - 1]);
				// (AS)
				for (int i = r - 1; i > l + 1 && i >= r - k; i--) {
					if (!match(i, '*')) break;
					add(g[l][r], f[l + 1][i - 1]);
				}
			}
			f[l][r] = g[l][r];
			// + Case 2
			if (match(l, '(')) {
				for (int mid = l + 1; mid < r; mid++) {
					// l ... mid
					int tmp = 0;
					add(tmp, f[mid + 1][r]); // AB
					//   [mid + 1, r]   -> SA
					add(tmp, h[mid + 1][r]);
					add(f[l][r], 1ll * tmp * g[l][mid] % mod);
				}
			}
			// h[l][r] l, r 表示成SA的方案数。

			for (int i = l; i < r && i <= l + k - 1; i++) {
				if (!match(i, '*')) break;
				add(h[l][r], f[i + 1][r]);
			}

		}
	}
	printf("%d\n", f[1][n]);
}