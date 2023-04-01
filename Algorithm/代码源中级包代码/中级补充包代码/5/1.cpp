#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1010;
int n, m, a[N], b[N], sg[N];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d", &b[i]);
	}
	for (int i = 1; i <= 1000; i++) {
		set<int> s;
		for (int j = 1; j <= m; j++)
			if (i >= b[j]) s.insert(sg[i - b[j]]);
		while (s.count(sg[i])) sg[i]++;
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
		ans ^= sg[a[i]];
	if (ans) {
		puts("YES");
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) if (a[i] >= b[j])
				if ((ans ^ sg[a[i]] ^ sg[a[i] - b[j]]) == 0) {
					printf("%d %d\n", i, b[j]);
					return 0;
				}
		}
	} else {
		puts("NO");
	}
}