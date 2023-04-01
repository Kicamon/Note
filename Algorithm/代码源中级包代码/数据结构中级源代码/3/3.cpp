#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000;

vector<int> vx;
vector<array<int, 4>> event;
int n, m;

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
	int t;
	info val;
} seg[N * 8];

// [l, r]

void update(int id) {
	seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}

void settag(int id, int t) {
	seg[id].val.minv = seg[id].val.minv + t;
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
	if (l == r) {
		seg[id].val = {0, vx[r] - vx[r - 1]};
	} else {
		int mid = (l + r) / 2;
		build(id * 2, l, mid);
		build(id * 2 + 1, mid + 1, r);
		update(id);
	}
}

void modify(int id, int l, int r, int ql, int qr, ll t) {
	if (l == ql && r == qr) {
		settag(id, t);
		return;
	}
	int mid = (l + r) / 2;
	pushdown(id);
	if (qr <= mid) modify(id * 2, l, mid, ql, qr, t);
	else if (ql > mid) modify(id * 2 + 1, mid + 1, r, ql,qr, t);
	else {
		modify(id * 2, l, mid, ql, mid, t);
		modify(id * 2 + 1, mid + 1, r, mid + 1, qr, t);
	}
	update(id);
} 

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int x1, x2, y1, y2;
		scanf("%d%d%d%d", &x1, &x2, &y1, &y2);
		vx.push_back(x1);
		vx.push_back(x2);
		// y坐标，类型，x坐标
		event.push_back({y1, 1, x1, x2});
		event.push_back({y2, -1, x1, x2});
	}
	sort(event.begin(), event.end());
	sort(vx.begin(), vx.end());
	vx.erase(unique(vx.begin(), vx.end()), vx.end());
	m = vx.size() - 1;
	build(1, 1, m);
	int totlen = seg[1].val.mincnt;
	int prey = 0;
	ll ans = 0;
	for (auto evt : event) {
		int cov = totlen;
		if (seg[1].val.minv == 0)
			cov = totlen - seg[1].val.mincnt;
		//printf("evt : %d %d %d %d\n",evt[0], evt[1], evt[2], evt[3]);
		//printf("%d %d\n",cov, prey);
		ans += (ll)(evt[0] - prey) * cov;
		prey = evt[0];
		int x1 = lower_bound(vx.begin(), vx.end(), evt[2]) - vx.begin() + 1;
		int x2 = lower_bound(vx.begin(), vx.end(), evt[3]) - vx.begin();
		if (x1 > x2) continue;
		modify(1, 1, m, x1, x2, evt[1]);
	}
	printf("%lld\n" ,ans);
}