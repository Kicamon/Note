#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 35100;

int n, k, a[N], last[N], pre[N], f[N];

struct node {
	int t, val;
} seg[N * 4];

// [l, r]

void update(int id) {
	seg[id].val = min(seg[id * 2].val, seg[id * 2 + 1].val);
}

void settag(int id, ll t) {
	seg[id].val = seg[id].val + t;
	seg[id].t = seg[id].t + t;
}

void pushdown(int id) {
	if (seg[id].t != 0) { // 标记非空
		settag(id * 2, seg[id].t);
		settag(id * 2 + 1, seg[id].t);
		seg[id].t = 0;
	}
}

void build(int id, int l, int r) {
	seg[id].t = 0;
	if (l == r) {
		seg[id].val = f[l];
	} else {
		int mid = (l + r) / 2;
		build(id * 2, l, mid);
		build(id * 2 + 1, mid + 1, r);
		update(id);
	}
}

// 节点为id，对应的区间为[l, r]，修改a[pos] -> val
void modify(int id, int l, int r, int ql, int qr, ll t) {
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
		return min(query(id * 2, l, mid, ql, mid),
			query(id * 2 + 1, mid + 1, r, mid + 1, qr));
	}
}

int main() {
	scanf("%d%d",&n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		last[i] = pre[a[i]];
		pre[a[i]] = i;
	}
	f[0] = 0;
	for (int i = 1; i <= n; i++) f[i] = 1 << 30;
	for (int j = 1; j <= k; j++) {
		build(1, 0, n);
		for (int i = 1; i <= n; i++) {
			if (last[i] != 0) modify(1, 0, n, 0, last[i] - 1, i - last[i]);
			f[i] = query(1, 0, n, 0, i - 1);
			//printf("%d %d %d\n", i, j, f[i]);
		}
	}
	printf("%d\n", f[n]);
}