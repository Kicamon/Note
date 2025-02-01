#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 101000;
const int M = 1010000;

int n, m, a[N], ans;
vector<int> pos[M];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		pos[a[i]].push_back(i);
	}
	for (int i = 1; i <= n + 1; i++) {
		ans += a[i] != a[i - 1];
	}
	for (int i = 0; i < m; i++) {
		int op;
		scanf("%d", &op);
		if (op == 2) {
			printf("%d\n", ans - 1);
		} else {
			int x, y;
			scanf("%d%d", &x, &y);
			if (x == y) continue;
			if (pos[x].size() > pos[y].size()) {
				pos[x].swap(pos[y]); // O(1)
				// swap(pos[x], pos[y]); O(1)
			}
			if (pos[y].empty()) continue;
			auto modify = [&](int p, int col) {
				ans -= (a[p] != a[p - 1]) + (a[p] != a[p + 1]);
				a[p] = col;
				ans += (a[p] != a[p - 1]) + (a[p] != a[p + 1]);
			};
			int col = a[pos[y][0]];
			for (int p : pos[x]) {
				modify(p, col);
				pos[y].push_back(p);
			}
			pos[x].clear();
		}
	}
}