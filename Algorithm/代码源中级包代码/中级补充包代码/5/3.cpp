#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, maxq, sg[20][20];
void solve() {
	scanf("%d%d", &n, &maxq);
	for (int a = 0; a <= 15; a++)
		for (int b = 0; b <= 10; b++) {
			set<int> s;
			sg[a][b] = 0;
			for (int p = 1; p <= a; p++) {
				int val = 0;
				for (int q = 1; p * q <= a && q <= maxq; q++) {
					val ^= sg[a - p * q][b];
					s.insert(val);
				}
			}
			for (int p = 1; p <= b; p++) {
				int val = 0;
				for (int q = 1; p * q <= b && q <= maxq; q++) {
					val ^= sg[a][b - p * q];
					s.insert(val);
				}
			}
			while (s.count(sg[a][b])) sg[a][b]++;
		}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		int v;
		scanf("%d", &v);
		if (v == 0) {
			int a = 0, b = 0, c = i;
			while (c % 2 == 0) c /= 2, a++;
			while (c % 3 == 0) c /= 3, b++;
			ans ^= sg[a][b];
		}
	}
	puts(ans ? "win" : "lose");
}

int main() {
	int tc;
	scanf("%d", &tc);
	for (int T = 0; T < tc; T++) {
		solve();
	}
}