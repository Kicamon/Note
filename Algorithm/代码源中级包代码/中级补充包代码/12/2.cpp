#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 801000;
array<int, 5> a[N], tmp[N];
int L, ans[N];

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
	// solve 把所有的点 按照 (x, y) 顺序排序
	int p1 = l, p2 = mid + 1;
	int p3 = 0;
	while (p1 <= mid || p2 <= r) {
		if (p2 > r || (p1 <= mid && make_pair(a[p1][0], a[p1][1]) <=
			make_pair(a[p2][0], a[p2][1]))) {
			if (a[p1][3] == 0) c.modify(a[p1][1], a[p1][2]);
			tmp[p3++] = a[p1++];
		} else {
			if (a[p2][3] != 0)
				ans[a[p2][2]] += a[p2][3] * c.query(a[p2][1]);
			tmp[p3++] = a[p2++];
		}
	}
	for (int i = l; i <= mid; i++)
		if (a[i][3] == 0) c.modify(a[i][1], -a[i][2]);
	for (int i = 0; i < p3; i++) a[l + i] = tmp[i];
}

int main() {
	scanf("%d", &L);
	c.init(L);
	int t = 0, q = 0;
	while (true) {
		int op;
		scanf("%d", &op);
		if (op == 3) break;
		if (op == 1) {
			int x, y, A;
			scanf("%d%d%d", &x, &y, &A);
			a[t++] = {x, y, A, 0};
		} else {
			int x1, y1, x2, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			a[t++] = {x2, y2, q, 1};
			a[t++] = {x1 - 1, y1 - 1, q, 1};
			a[t++] = {x2, y1 - 1, q, -1};
			a[t++] = {x1 - 1, y2, q, -1};
			q++;
		}
	}
	solve(0, t - 1);
	for (int i = 0; i < q; i++) {
		printf("%d\n", ans[i]);
	}
}