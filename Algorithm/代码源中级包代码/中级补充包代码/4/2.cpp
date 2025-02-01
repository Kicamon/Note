#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 210;

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
}
