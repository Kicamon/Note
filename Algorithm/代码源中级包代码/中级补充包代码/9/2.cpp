#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 5010;
const int M = (1 << 20) + 10;

int n, a[N], vis[M];
vector<pair<int,int>> ans1, ans2;

void dfs(int x, int y, int sum, int mask, vector<pair<int,int>> &ans) {
	if (x == y) {
		ans.push_back(make_pair(sum, mask));
	} else {
		dfs(x + 1, y, sum, mask, ans);
		dfs(x + 1, y, sum + a[x], mask | (1 << x), ans);
		dfs(x + 1, y, sum - a[x], mask | (1 << x), ans);
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	int M = n / 2;
	dfs(0, M, 0, 0, ans1);
	dfs(M, n, 0, 0, ans2);
	sort(ans1.begin(), ans1.end());
	ans1.erase(unique(ans1.begin(), ans1.end()), ans1.end());
	sort(ans2.begin(), ans2.end());
	ans2.erase(unique(ans2.begin(), ans2.end()), ans2.end());
	for (auto [sum, mask] : ans1) {
		for (int j = lower_bound(ans2.begin(), ans2.end(), make_pair(-sum, -1)) - ans2.begin();
			j < ans2.size() && ans2[j].first == -sum; j++) {
			vis[mask | ans2[j].second] = 1;
		}
	}
	int ans = 0;
	for (int i = 0; i < (1 << n); i++) ans += vis[i];
	printf("%d\n", ans - 1);
}