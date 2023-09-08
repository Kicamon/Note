#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 100010;
int n, m;
char s[N], t[N];
bitset<N> f, g[28];

int main() {
	scanf("%s", s);
	scanf("%s", t);
	int n = strlen(s), m = strlen(t);
	for (int i = 0; i <= n - m; i++)
		f[i] = 1;
	for (int i = 0; i < n; i++) {
		g[s[i] - 'a'][i] = 1;
	}
	for (int j = 0; j < m; j++) {
		if (t[j] == '?') continue;
		f &= g[t[j] - 'a'] >> j;
	}
	printf("%d\n", f.count());
	for (int i = 0; i < n; i++) if (f[i]) {
		printf("%d\n", i);
	}
}