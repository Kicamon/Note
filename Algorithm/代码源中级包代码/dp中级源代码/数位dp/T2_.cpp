#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int vis[11];
vector<int> d;
int n, k;

// 至少k个不同的位？

bool dfs(int x, bool larger, int cnt, int num) { // 搜到了第x位，前x位是不是大于n的前x位，前x位有多少种不同的数字。
	if (x == d.size()) {
		printf("%d\n", num);
		return true;
	} else {
		for (int i = larger ? 0 : d[x]; i <= 9; i++) {
			vis[i] += 1;
			int ncnt = cnt;
			if (vis[i] == 1) ncnt += 1;
			if (ncnt + (int)d.size() - x - 1 >= k && 
				dfs(x + 1, larger | (i > d[x]), ncnt, num * 10 + i)) {
				return true;
			}
			vis[i] -= 1;
		}
		return false;
	}
}

void solve() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i <= 9; i++) vis[i] = 0;
	d.clear();
	while (n) {
		d.push_back(n % 10);
		n /= 10;
	}
	reverse(d.begin(), d.end());
	while (true) {
		if (dfs(0, 0, 0, 0)) break;
		int m = d.size() + 1;
		d.clear();
		d.push_back(1);
		for (int i = 0; i < m - 1; i++) d.push_back(0);
	}
}

int main() {
	int tc;
	scanf("%d", &tc);
	for (int i = 0; i < tc; i++) {
		solve();
	}
}