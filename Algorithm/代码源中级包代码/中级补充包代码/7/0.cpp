#include <bits/stdc++.h>
using namespace std;

const int N = 101000;
char s[N];
int sa[N], rk[N], ht[N], n;
array<int, 3> p[N];
void buildSA(char *s, int *sa, int *rk, int n) {
	for (int k = 1; k <= n; k = k * 2) {
		if (k == 1) {
			for (int i = 0; i < n; i++)
				p[i] = {s[i], 0, i};
		} else {
			for (int i = 0; i < n; i++) {
				if (i + k / 2 >= n) p[i] = {rk[i], 0, i};
				else p[i] = {rk[i], rk[i + k / 2], i};
			}
		}
		sort(p, p + n);
		int t = 0;
		for (int i = 0; i < n; i++) {
			if (i == 0 || p[i][0] != p[i - 1][0] || p[i][1] != p[i - 1][1]) {
				rk[p[i][2]] = t++;
			} else {
				rk[p[i][2]] = rk[p[i - 1][2]];
			}
		}
		if (t == n) break;
	}
	for (int i = 0; i < n; i++) sa[rk[i]] = i;
}

int main() {
	scanf("%s", s);
	n = strlen(s);
	buildSA(s, sa, rk, n);
	for (int i = 0; i < n; i++) printf("%d ", sa[i]); puts("");
	for (int i = 0; i < n; i++) printf("%d ", rk[i]); puts("");
}