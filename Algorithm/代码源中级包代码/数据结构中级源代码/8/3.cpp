#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000;
int n;
int a[N], pre[N], nxt[N];

bool solve(int l, int r) {
	if (l > r) return true;
	for (int pl = l, pr = r; pl <= pr; pl++, pr--) {
		if (pre[pl] < l && nxt[pl] > r) 
			return solve(l, pl - 1) && solve(pl + 1, r);
		if (pre[pr] < l && nxt[pr] > r) 
			return solve(l, pr - 1) && solve(pr + 1, r);
	}
	return false;
}

bool solve() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	map<int, int> pos;
	for (int i = 1; i <= n; i++) {
		if (pos.count(a[i])) pre[i] = pos[a[i]];
		else pre[i] = 0;
		pos[a[i]] = i;
	}
	pos.clear();
	for (int i = n; i >= 1; i--) {
		if (pos.count(a[i])) nxt[i] = pos[a[i]];
		else nxt[i] = n + 1;
		pos[a[i]] = i;
	}
	return solve(1, n);
}

int main() {
	int tc;
	scanf("%d", &tc);
	for (int T = 0; T < tc; T++) {
		puts(solve() ? "non-boring" : "boring");
	}
}