#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll dp[20][2][10][5];

ll dfs(int rem, int exist, int last, int inc) { // 还剩多少位，存不存在连续三位递增，末尾的数值，末尾的递增长度
	if (rem == 0) {
		return exist;
	}
	if (dp[rem][exist][last][inc] != -1) {
		return dp[rem][exist][last][inc];
	}
	ll &ans = dp[rem][exist][last][inc];
	ans = 0;
	for (int i = 0; i <= 9; i++) {
		int inc_ = (i > last)? min(inc + 1, 3) : 1;
		ans += dfs(rem - 1, exist | (inc_ == 3), i, inc_);
	}
	return ans;
}

ll solve(ll x) {  // 1 ... x
	x += 1; // 1 ... x - 1
	vector<int> d;
	while (x) {
		d.push_back(x % 10);
		x /= 10;
	}
	reverse(d.begin(), d.end());
	int m = d.size();
	// 前导0
	ll ans = 0;
	for (int i = 1; i <= m - 1; i++) {
		for (int j = 1; j <= 9; j++)
			ans += dfs(i - 1, 0, j, 1);
	}
	int exist = 0, last = 0, inc = 0;
	for (int i = 0; i < m; i++) {
		for (int j = (i == 0) ? 1 : 0; j < d[i]; j++) {
			int inc_ = (j > last)? min(inc + 1, 3) : 1;
			ans += dfs(m - i - 1, exist | (inc_ == 3), j, inc_);
		}
		inc = (d[i] > last)? min(inc + 1, 3) : 1;
		exist |= (inc == 3);
		last = d[i];
	}
	return ans;
}

int main() {
	ll l, r;
	scanf("%lld%lld", &l, &r);
	memset(dp, -1 ,sizeof(dp));
	printf("%lld\n", solve(r) - solve(l - 1));
}