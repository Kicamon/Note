#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
int main() {
	int tc;
	scanf("%d", &tc);
	for (int T = 0; T < tc; T++) {
		scanf("%d", &n);
		int ans = 0;
		for (int i = 0; i < n; i+= 2) {
			int x, y;
			scanf("%d%d", &x, &y);
			ans ^= __builtin_ctz(((x - 1) | (y - 1)) + 1);
		}
		puts(ans? "YES" : "NO");
	}
}