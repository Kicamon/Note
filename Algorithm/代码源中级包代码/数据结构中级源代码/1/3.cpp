#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long u64;

const int N = 201000;
int n, q;

// Binary Index Tree
// Fenwick's Tree
template<class T>
struct BIT {
	T c[N];
	int size;
	void resize(int s) { size = s;}
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

BIT<u64> c1, c2;   // c1 d[i] c2 i*d[i]

int main() {
	scanf("%d%d", &n, &q);
	c1.resize(n);
	c2.resize(n);
	for (int i = 0; i < q; i++) {
		int ty;
		scanf("%d", &ty);
		if (ty == 1) {
			int l, r;
			u64 d;
			scanf("%d%d%llu", &l, &r, &d);
			c1.modify(l, d);
			c1.modify(r + 1, -d);
			c2.modify(l, l * d);
			c2.modify(r + 1, (r + 1) * (-d));
		} else {
			int x;
			scanf("%d", &x);
			u64 ans = (x + 1) * c1.query(x) - c2.query(x);
			printf("%llu\n", ans);
		}
	}
}