#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

map<pair<ll, vector<int>>, ll> dp;
int m, a[110];
ll L;

vector<int> reduce(vector<int> a) {
	vector<int> a_;
	for (int i = 0; i < a.size(); i += 2) {
		a_.push_back(a[i]);
		if (i + 1 < a.size() && a[i] == a[i + 1]) {
			return vector<int>(0);
		}
	}
	return a_;
}

ll calc(ll L, vector<int> a) {
	if (a.empty()) return 0;
	if (dp.count(make_pair(L, a))) {
		return dp[make_pair(L, a)];
	}
	if (L == 0) {
		int m = a.size();
		int ans = 1;
		for (int i = 0; i < m; i++) {
			if (__builtin_parity(i) != a[i]) {
				ans = 0;
				break;
			}
		}
		return dp[make_pair(L, a)] = ans;
	}
	ll ans = 0;
	ans += calc(L / 2, reduce(a));
	auto b = a;
	b.insert(b.begin(), a[0]^1);
	ans += calc((L - 1) / 2, reduce(b));
	return dp[make_pair(L, a)] = ans;
}

void solve() {
	scanf("%d%lld", &m, &L);
	for (int i = 0; i < m; i++) scanf("%d", &a[i]);
	dp.clear();
	printf("%lld\n", calc(L, vector<int>(a, a + m)));
}

int main() {
	int tc;
	scanf("%d", &tc);
	for (int i = 0; i < tc; i++) {
		solve();
	}
}