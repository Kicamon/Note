#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int B = 60;

struct linear_basis {
	ll num[B + 1];
	bool insert(ll x) {
		for (int i = B - 1; i >= 0; i--) {
			if (x & (1ll << i)) {
				if (num[i] == 0) { num[i] = x; return true; }
				x ^= num[i];
			}
		}
		return false;
	}
	ll querymin(ll x) {
		for (int i = B - 1; i >= 0; i--) {
			x = min(x, x ^ num[i]);
		}
		return x;
	}
	ll querymax(ll x) {
		for (int i = B - 1; i >= 0; i--) {
			x = max(x, x ^ num[i]);
		}
		return x;
	}
}T;

int n;
ll k;
int main() {
	scanf("%d%lld",&n, &k);
	int zero = 0;
	for (int i = 0; i < n; i++) {
		ll x;
		scanf("%lld", &x);
		if (!T.insert(x)) zero++;
	}
	k >>= zero;
	vector<ll> num;
	for (int i = 0; i <= B - 1; i++) if (T.num[i] != 0) {
		num.push_back(T.num[i]);
	}
	int m = num.size();
	ll x = 0;
	for (int i = m - 1; i >= 0; i--) {
		if (k & (1ll << i)) {
			x = max(x, x ^ num[i]);
		} else {
			x = min(x, x ^ num[i]);
		}
	}
	printf("%lld\n", x);
}