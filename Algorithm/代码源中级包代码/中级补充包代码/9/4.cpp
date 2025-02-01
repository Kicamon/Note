#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, a[44];
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	int M = n / 2;
	auto getsum = [&](int l, int r) {
		// l .. r - 1
		vector<int> s{0};
		for (int i = l; i < r; i++) {
			vector<int> t = s;
			for (auto u : s) t.push_back(u + a[i]);
			s = t;
		}
		vector<array<int, 2>> ans;
		for (auto p : s) ans.push_back({0, p});
		return ans;
	};

	ll ans = 0;
	vector<array<int, 2>> s1 = getsum(0, M);
	vector<array<int, 2>> s2 = getsum(M, n);
	for (int d = 0, pw = 1; d <= 8; pw *= 10, d++) {
		auto reorder = [&](vector<array<int, 2>> &s, int pw) {
			static int cnt[20];
			for (int i = 0; i <= 9; i++) cnt[i] = 0;
			for (auto [rem, val] : s) cnt[val / pw % 10]++;
			for (int i = 1; i <= 9; i++) cnt[i] += cnt[i - 1];
			int m = s.size();
			vector<array<int, 2>> t(m, {0, 0});
			for (int i = m - 1; i >= 0; i--) {
				t[--cnt[s[i][1] / pw % 10]] = {s[i][1] % (pw * 10), s[i][1]};
			}
			s = t;
		};
		auto calc = [&](int d) {
			int r = s2.size();
			ll ans = 0;
			for (int l = 0; l < s1.size(); l++) {
				while (r > 0 && s2[r - 1][0] + s1[l][0] > d) --r;
				ans += r;
			}
			return ans;
		};
		reorder(s1, pw);
		reorder(s2, pw);
		ans += calc(5 * pw - 1) - calc(4 * pw - 1) + calc(15 * pw - 1) - calc(14 * pw - 1);
	}
	printf("%lld\n", ans);
}