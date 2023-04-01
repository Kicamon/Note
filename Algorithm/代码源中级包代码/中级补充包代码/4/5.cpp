#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int B = 60;

struct linear_basis {
	ll num[B + 1];
	int t[B + 1];
	void insert(ll x, int t_) {
		for (int i = B - 1; i >= 0; i--) {
			if (x & (1ll << i)) {
				if (num[i] == 0) {
					num[i] = x;
					t[i] = t_;
					return;
				} else {
					if (t[i] < t_) {
						swap(t[i], t_);
						swap(num[i], x);
					}
					x ^= num[i];
				}
			}
		}
	}
	ll querymax(int t_, ll x = 0) {
		for (int i = B - 1; i >= 0; i--) {
			if (t[i] >= t_) x = max(x, x ^ num[i]);
		}
		return x;
	}
}T;

const int N = 200100;
int n, m;
vector<pair<int, int>> q[N];
ll a[N], ans[N];
int main() {
	scanf("%d%d",&n, &m);
	for (int i = 1; i <= n; i++) scanf("%lld" ,&a[i]);
	for (int i = 0; i < m; i++) {
		int l, r;
		scanf("%d%d", &l, &r);
		q[r].push_back(make_pair(l, i));
	}
	for (int i = 1; i <= n; i++) {
		T.insert(a[i], i);
		for (auto [l, id]: q[i]) {
			ans[id] = T.querymax(l);
		}
	}
	for (int i = 0; i < m; i++) printf("%lld\n", ans[i]);
}