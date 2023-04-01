#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000;
array<int, 5> a[N], tmp[N];
int n, L, ans[N];

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

void solve(int l, int r) {
	if (l == r) {
		return;
	}
	int mid = (l + r) >> 1;
	solve(l, mid);
	solve(mid + 1, r);
	// solve 把所有的点 按照 (y, z) 顺序排序
	int p1 = l, p2 = mid + 1;
	int p3 = 0;
	while (p1 <= mid || p2 <= r) {
		if (p2 > r || (p1 <= mid && make_pair(a[p1][1], a[p1][2]) <=
			make_pair(a[p2][1], a[p2][2]))) {
			c.modify(a[p1][2], a[p1][3]);
			tmp[p3++] = a[p1++];
		} else {
			a[p2][4] += c.query(a[p2][2]);
			tmp[p3++] = a[p2++];
		}
	}
	for (int i = l; i <= mid; i++)
		c.modify(a[i][2], -a[i][3]);
	for (int i = 0; i < p3; i++) a[l + i] = tmp[i];
}

int main() {
	scanf("%d%d", &n, &L);
	c.init(L);
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &a[i][0], &a[i][1], &a[i][2]);
		a[i][3] = 1;
	}
	sort(a, a + n);
	int t = 0;
	for (int i = 0; i < n; i++) {
		if (t != 0 && (a[i][0] == a[t - 1][0] && a[i][1] == a[t - 1][1]
			&& a[i][2] == a[t - 1][2])) {
			a[t - 1][3] += 1;
		} else {
			a[t++] = a[i];
		}
	}
	solve(0, t - 1);
	for (int i = 0; i < t; i++) {
		ans[a[i][3] + a[i][4] - 1] += a[i][3];
	}
	for (int i = 0; i < n; i++) {
		printf("%d\n", ans[i]);
	}
}