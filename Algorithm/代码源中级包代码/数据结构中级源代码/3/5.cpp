#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000;

int n, q, a[N], ans[N];
vector<pair<int,int>> qu[N];

struct node {
	int val;
} seg[N * 4];

void update(int id) {
	seg[id].val = min(seg[id * 2].val, seg[id * 2 + 1].val);
}

void change(int id, int l, int r, int pos, int val) {
	if (l == r) {
		seg[id].val = val;
	} else {
		int mid = (l + r) / 2;
		if (pos <= mid) change(id * 2, l, mid, pos, val);
		else change(id * 2 + 1, mid + 1, r, pos, val);
		update(id);
	}
}

int search(int id, int l, int r, int d) {
	if (l == r) return l;
	int mid = (l + r) / 2;
	if (seg[id * 2].val < d) return search(id * 2, l, mid, d);
	else return search(id * 2 + 1, mid + 1, r, d);
} 

int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		a[i] = min(a[i], n + 1);
	}
	for (int i = 1; i <= q;i++) {
		int l, r;
		scanf("%d%d", &l, &r);
		qu[r].push_back({l, i});
	}
	for (int r = 1; r <= n; r++) {
		change(1, 0, n + 1, a[r], r);
		for (auto que : qu[r]) {
			ans[que.second] = search(1, 0, n + 1, que.first);
		}
	}
	for (int i = 1; i <= q; i++) {
		printf("%d\n", ans[i]);
	}
}