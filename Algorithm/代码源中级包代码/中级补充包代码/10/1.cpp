#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
bitset<2000001> f;

int main() {
	scanf("%d", &n);
	f[0] = 1;
	for (int i = 0; i < n; i++) {
		int x;
		scanf("%d", &x);
		f = f | (f << x);
	}
	int ans = 0;
	for (int i = 0; i <= 2000000; i++)
		if (f[i]) ans ^= i;
	printf("%d\n", ans);
}