#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000;
const int inf = 1 << 30;

int n, q;
int a[N], ans[N];

struct node {
	int minv;
} seg[N * 4];

// [l, r]

void update(int id) {
	seg[id].minv = min(seg[id * 2].minv, seg[id * 2 + 1].minv);
}

void build(int id, int l, int r) {
	if (l == r) {
		seg[id].minv = inf;
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
		seg[id].minv = val;
	} else {
		int mid = (l + r) / 2;
		if (pos <= mid) change(id * 2, l, mid, pos, val);
		else change(id * 2 + 1, mid + 1, r, pos, val);
		// 重要‼️
		update(id);
	}
} 
// [ql, qr]表示查询的区间
int query(int id, int l, int r, int ql, int qr) {
	if (l == ql && r == qr) return seg[id].minv;
	int mid = (l + r) / 2;
	// [l, mid] , [mid + 1, r]
	if (qr <= mid) return query(id * 2, l, mid, ql, qr);
	else if (ql > mid) return query(id * 2 + 1, mid + 1, r, ql,qr);
	else {
		// qr > mid, ql <= mid
		// [ql, mid], [mid + 1, qr]
		return min(query(id * 2, l, mid, ql, mid), 
			query(id * 2 + 1, mid + 1, r, mid + 1, qr));
	}
}

vector<array<int,4>> event;

int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		event.push_back({-a[i], 0, i, 0});
	}
	for (int i = 1; i <= q; i++) {
		int l, r, x;
		scanf("%d%d%d", &l, &r, &x);
		event.push_back({-x, i, l, r});
	}
	sort(event.begin(), event.end());
	build(1, 1, n);
	for (auto evt : event) {
		if (evt[1] == 0) change(1, 1, n, evt[2], -evt[0]);
		else ans[evt[1]] = query(1, 1, n, evt[2], evt[3]);
	}
	for (int i = 1; i <= q; i++) {
		if (ans[i] == inf) ans[i] = -1;
		printf("%d\n", ans[i]);
	}
}