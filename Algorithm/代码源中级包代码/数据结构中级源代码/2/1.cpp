#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000;

int n, q;
int a[N];

struct info {
	int minv, mincnt;
};

info operator + (const info &l, const info &r) {
	info a;
	a.minv = min(l.minv, r.minv);
	if (l.minv == r.minv) a.mincnt = l.mincnt + r.mincnt;
	else if (l.minv < r.minv) a.mincnt = l.mincnt;
	else a.mincnt = r.mincnt;
	return a;
}

struct node {
	info val;
} seg[N * 4];

// [l, r]

void update(int id) {
	seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}

void build(int id, int l, int r) {
	if (l == r) {
		seg[id].val = {a[l], 1};
	} else {
		int mid = (l + r) / 2;
		build(id * 2, l, mid);
		build(id * 2 + 1, mid + 1, r);
		update(id);
	}
}

// 节点为id，对应的区间为[l, r]，修改a[pos] -> val
void change(int id, int l, int r, int pos, int val) {
	if (l == r) {
		seg[id].val = {val, 1};
	} else {
		int mid = (l + r) / 2;
		if (pos <= mid) change(id * 2, l, mid, pos, val);
		else change(id * 2 + 1, mid + 1, r, pos, val);
		// 重要‼️
		update(id);
	}
} 
// [ql, qr]表示查询的区间
info query(int id, int l, int r, int ql, int qr) {
	if (l == ql && r == qr) return seg[id].val;
	int mid = (l + r) / 2;
	// [l, mid] , [mid + 1, r]
	if (qr <= mid) return query(id * 2, l, mid, ql, qr);
	else if (ql > mid) return query(id * 2 + 1, mid + 1, r, ql,qr);
	else {
		// qr > mid, ql <= mid
		// [ql, mid], [mid + 1, qr]
		return query(id * 2, l, mid, ql, mid) + 
			query(id * 2 + 1, mid + 1, r, mid + 1, qr);
	}
}

int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	build(1, 1, n);
	for (int i = 0; i < q; i++) {
		int ty;
		scanf("%d", &ty);
		if (ty == 1) {
			int x, d;
			scanf("%d%d", &x, &d);
			change(1, 1, n, x, d);
		} else {
			int l, r;
			scanf("%d%d", &l, &r);
			auto ans = query(1, 1, n, l, r);
			printf("%d %d\n", ans.minv, ans.mincnt);
		}
	}
}