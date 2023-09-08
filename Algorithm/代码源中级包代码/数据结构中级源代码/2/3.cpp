#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000;

int n, q;
int a[N];

struct info {
	ll maxv;
};
struct tag {
	ll add;
};

info operator + (const info &l, const info &r) {
	return {max(l.maxv, r.maxv)};
}

info operator + (const info &v, const tag &t) {
	return {v.maxv + t.add};
}

tag operator + (const tag &t1, const tag &t2) {
	return {t1.add + t2.add};
}

struct node {
	tag t;
	info val;
} seg[N * 4];

// [l, r]

void update(int id) {
	seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}

void settag(int id, tag t) {
	seg[id].val = seg[id].val + t;
	seg[id].t = seg[id].t + t;
}

void pushdown(int id) {
	if (seg[id].t.add != 0) { // 标记非空
		settag(id * 2, seg[id].t);
		settag(id * 2 + 1, seg[id].t);
		seg[id].t.add = 0;
	}
}

void build(int id, int l, int r) {
	if (l == r) {
		seg[id].val = {a[l]};
	} else {
		int mid = (l + r) / 2;
		build(id * 2, l, mid);
		build(id * 2 + 1, mid + 1, r);
		update(id);
	}
}

// 节点为id，对应的区间为[l, r]，修改a[pos] -> val
void modify(int id, int l, int r, int ql, int qr, tag t) {
	if (l == ql && r == qr) {
		settag(id, t);
		return;
	}
	int mid = (l + r) / 2;
	// 重要‼️
	pushdown(id);
	if (qr <= mid) modify(id * 2, l, mid, ql, qr, t);
	else if (ql > mid) modify(id * 2 + 1, mid + 1, r, ql,qr, t);
	else {
		modify(id * 2, l, mid, ql, mid, t);
		modify(id * 2 + 1, mid + 1, r, mid + 1, qr, t);
	}
	// 重要‼️
	update(id);
} 
// [ql, qr]表示查询的区间
info query(int id, int l, int r, int ql, int qr) {
	if (l == ql && r == qr) return seg[id].val;
	int mid = (l + r) / 2;
	// 重要‼️
	pushdown(id);
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
			int l, r, d;
			scanf("%d%d%d", &l, &r, &d);
			modify(1, 1, n, l, r, (tag){d});
		} else {
			int l, r;
			scanf("%d%d", &l, &r);
			auto ans = query(1, 1, n, l, r);
			printf("%lld\n", ans.maxv);
		}
	}
}