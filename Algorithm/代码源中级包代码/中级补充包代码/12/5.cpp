#include<bits/stdc++.h>
using namespace std;
typedef double db;

const int N = 101000;
int n;

struct node {
	int h, v, id;
} a[N], tmp[N];
struct info {
	int mx;
	db cnt;
} ans[N], ans2[N];;
info operator + (info a, info b) {
	info c{0, 0};
	c.mx = max(a.mx, b.mx);
	if (a.mx == c.mx) c.cnt += a.cnt;
	if (b.mx == c.mx) c.cnt += b.cnt;
	return c;
}

info zero{-(1 << 30), 0};

template<class T>
struct BIT {
	T c[N];
	int size;
	void init(int s) {
		size = s;
		for (int i = 1; i <= s; i++) c[i] = zero;
	}
	T query(int x) { // 1 ... x
		assert(x <= size);
		T s = zero;
		for (; x; x -= x & (-x)) {
			s = s + c[x];
		}
		return s;
	}

	void modify(int x, T s) { // a[x] += s
		assert(x != 0);
		for (; x <= size; x += x & (-x)) {
			c[x] = c[x] + s;
		}
	}
	void clear(int x) {
		for (; x <= size; x += x & (-x)) {
			c[x] = zero;
		}
	}
};
BIT<info> c;

void solve(int l, int r) {
	if (l == r) {
		if (ans[l].mx == 0) ans[l] = (info){1, 1};
		return;
	}
	int mid = (l + r) >> 1;
	solve(l, mid);
	for (int i = l; i <= r; i++) tmp[i] = a[i];
	sort(a + l, a + mid + 1, [&](node a, node b) {
		return make_pair(a.h, a.v) < make_pair(b.h, b.v);
	});
	sort(a + mid + 1, a + r + 1, [&](node a, node b) {
		return make_pair(a.h, a.v) < make_pair(b.h, b.v);
	});

	int pl = l;
	for (int pr = mid + 1; pr <= r; pr++) {
		while (pl <= mid && make_pair(a[pl].h, a[pl].v) <= 
			make_pair(a[pr].h, a[pr].v)) {
			c.modify(a[pl].v, ans[a[pl].id]);
			pl++;
		}
		info cur = c.query(a[pr].v);
		cur.mx += 1;
		ans[a[pr].id] = ans[a[pr].id] + cur;
	}
	for (int i = l; i < pl; i++) c.clear(a[i].v);
	for (int i = l; i <= r; i++) a[i] = tmp[i];
	solve(mid + 1, r);
}
int main() {
	scanf("%d", &n);
	vector<int> v;
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &a[i].h, &a[i].v);
		a[i].h = -a[i].h;
		a[i].v = -a[i].v;
		a[i].id = i;
		v.push_back(a[i].v);
	}
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	int m = v.size();
	for (int i = 1; i <= n; i++) {
		a[i].v = lower_bound(v.begin(), v.end(), a[i].v) - v.begin() + 1;
	}
	c.init(m);
	solve(1, n);
	info t{0, 0};
	for (int i = 1; i <= n; i++) {
		ans2[i] = ans[i];
		t = t + ans[i];
		ans[i] = {0, 0};
		a[i].id = n + 1 - a[i].id;
		a[i].h = -a[i].h;
		a[i].v = m + 1 - a[i].v;
	}
	reverse(a + 1, a + n + 1);
	solve(1, n);
	reverse(ans + 1, ans + n + 1);
	printf("%d\n", t.mx);
	for (int i = 1; i <= n; i++) {
		if (ans[i].mx + ans2[i].mx != t.mx + 1) printf("0\n");
		else printf("%.9f\n", ans[i].cnt * ans2[i].cnt / t.cnt);
	}
	return 0;
}
