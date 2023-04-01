#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 801000;
array<int, 4> tmp[N];
int n, m, a[N], pos[N], t[N];
ll ans[N];

template<class T>
struct BIT {
	T c[N];
	int size;
	void init(int s) {
		size = s;
		for (int i = 1; i <= s; i++) c[i] = 0;
	}
	T query(int x) { // 1 ... x
		assert(x <= size);
		T s = 0;
		for (; x; x -= x & (-x)) {
			s += c[x];
		}
		return s;
	}

	void modify(int x, T s) { // a[x] += s
		assert(x != 0);
		for (; x <= size; x += x & (-x)) {
			c[x] += s;
		}
	} 
};

BIT<int> c;

vector<int> solve(vector<array<int, 4>> &a) {
	int n = a.size();
	vector<int> ans(n + 1, 0);
	function<void(int, int)> solve = [&](int l, int r) {
		if (l == r) {
			return;
		}
		int mid = (l + r) >> 1;
		solve(l, mid);
		solve(mid + 1, r);
		// solve 把所有的点 按照 (x, y) 顺序排序
		int p1 = l, p2 = mid + 1;
		int p3 = 0;
		while (p1 <= mid || p2 <= r) {
			if (p2 > r || (p1 <= mid && make_pair(a[p1][1], a[p1][2]) <=
				make_pair(a[p2][1], a[p2][2]))) {
				c.modify(a[p1][2], 1);
				tmp[p3++] = a[p1++];
			} else {
				ans[a[p2][3]] += c.query(a[p2][2]);
				tmp[p3++] = a[p2++];
			}
		}
		for (int i = l; i <= mid; i++)
			c.modify(a[i][2], -1);
		for (int i = 0; i < p3; i++) a[l + i] = tmp[i];
	};
	sort(a.begin(), a.end());
	solve(0, n - 1);
	return ans;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		pos[a[i]] = i;
	}
	for (int i = 1; i <= m; i++) {
		int v;
		scanf("%d", &v);
		t[pos[v]] = i;
	}
	int cnt = m;
	for (int i = 1; i <= n; i++)
		if (t[i] == 0) t[i] = ++cnt;
	c.init(n);
	vector<array<int, 4>> p;
	for (int i = 1; i <= n; i++) {
		p.push_back({n + 1 - t[i], i, n + 1 - a[i], i});
	}
	auto ans1 = solve(p);
	for (int i = 1; i <= n; i++) ans[t[i]] += ans1[i];
	p.clear();
	for (int i = 1; i <= n; i++) {
		p.push_back({n + 1 - t[i], n + 1 - i, a[i], i});
	}
	auto ans2 = solve(p);
	for (int i = 1; i <= n; i++) ans[t[i]] += ans2[i];
	for (int i = n; i >= 1; i--) ans[i] += ans[i + 1];
	for (int i = 1; i <= m; i++) printf("%lld\n", ans[i]);
}