#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000;

int n, q;
int a[N];

struct node {
	int val;
} seg[N * 4];

// [l, r]

void update(int id) {
	seg[id].val = max(seg[id * 2].val, seg[id * 2 + 1].val);
}

void build(int id, int l, int r) {
	if (l == r) {
		seg[id].val = a[l];
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
		seg[id].val = val;
	} else {
		int mid = (l + r) / 2;
		if (pos <= mid) change(id * 2, l, mid, pos, val);
		else change(id * 2 + 1, mid + 1, r, pos, val);
		// 重要‼️
		update(id);
	}
}

int search(int id, int l, int r, int ql, int qr, int d) {
	if (l == ql && r == qr) {
		if (seg[id].val < d) return -1;
		else {
			if (l == r) return l;
			int mid = (l + r) / 2;
			if (seg[id * 2].val >= d) return search(id * 2, l, mid, ql, mid, d);
			else return search(id * 2 + 1, mid + 1, r, mid + 1, qr, d);
		}
	}
	int mid = (l + r) / 2;
	// [l, mid] , [mid + 1, r]
	if (qr <= mid) return search(id * 2, l, mid, ql, qr, d);
	else if (ql > mid) return search(id * 2 + 1, mid + 1, r, ql, qr, d);
	else {
		int pos = search(id * 2, l, mid, ql, mid, d);
		if (pos == -1) return search(id * 2 + 1, mid + 1, r, mid + 1, qr, d);
		else return pos;
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
			int l, r, d;
			scanf("%d%d%d", &l, &r, &d);
			auto ans = search(1, 1, n, l, r, d);
			printf("%d\n", ans);
		}
	}
}