#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000;
const ll mod = 1000000007;

int n, q;
int a[N];

struct tag {
	ll mul, add;
};

tag operator + (const tag &t1, const tag &t2) {
	// (x * t1.mul + t1.add) * t2.mul + t2.add
	return {t1.mul * t2.mul % mod, (t1.add * t2.mul + t2.add) % mod};
}

struct node {
	tag t;
	ll val;
	int sz;
} seg[N * 4];

// [l, r]

void update(int id) {
	seg[id].val = (seg[id * 2].val + seg[id * 2 + 1].val) % mod;
}

void settag(int id, tag t) {
	seg[id].t = seg[id].t + t;
	seg[id].val = (seg[id].val * t.mul + seg[id].sz * t.add) % mod;
}

void pushdown(int id) {
	if (seg[id].t.mul != 1 || seg[id].t.add != 0) { // 标记非空
		settag(id * 2, seg[id].t);
		settag(id * 2 + 1, seg[id].t);
		seg[id].t.mul = 1;
		seg[id].t.add = 0;
	}
}

void build(int id, int l, int r) {
	seg[id].t = {1, 0};
	seg[id].sz = r - l + 1;
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
ll query(int id, int l, int r, int ql, int qr) {
	if (l == ql && r == qr) return seg[id].val;
	int mid = (l + r) / 2;
	// 重要‼️
	pushdown(id);
	if (qr <= mid) return query(id * 2, l, mid, ql, qr);
	else if (ql > mid) return query(id * 2 + 1, mid + 1, r, ql,qr);
	else {
		// qr > mid, ql <= mid
		// [ql, mid], [mid + 1, qr]
		return (query(id * 2, l, mid, ql, mid) + 
			query(id * 2 + 1, mid + 1, r, mid + 1, qr)) % mod;
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
		if (ty <= 3) {
			int l, r, d;
			scanf("%d%d%d", &l, &r, &d);
			if (ty == 1) modify(1, 1, n, l, r, (tag){1, d});
			else if (ty == 2) modify(1, 1, n, l, r, (tag){d, 0});
			else modify(1, 1, n, l, r, (tag){0, d});
		} else {
			int l, r;
			scanf("%d%d", &l, &r);
			auto ans = query(1, 1, n, l, r);
			printf("%lld\n", ans);
		}
	}
}