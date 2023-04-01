#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000;
const int M = 30;

struct node {
	int s[2];
	int sz;
}seg[N * 32];
int tot = 0, root;
int n, m;

int main() {
	scanf("%d%d", &n, &m);
	root = ++tot;
	for (int i = 0; i < n; i++) {
		int x;
		scanf("%d", &x);
		int p = root;
		for (int j = M - 1; j >= 0; j--) {
			seg[p].sz += 1;
			int w = (x >> j) & 1;
			if (seg[p].s[w] == 0) seg[p].s[w] = ++tot;
			p = seg[p].s[w];
		}
		seg[p].sz += 1;
	}
	for (int i = 0; i < m; i++) {
		int x, k;
		scanf("%d%d", &x, &k);
		int p = root;
		int ans = 0;
		for (int j = M - 1; j>= 0; j--) {
			int w = (x >> j) & 1;
			if (seg[seg[p].s[w]].sz >= k) {
				p = seg[p].s[w];
			} else {
				k -= seg[seg[p].s[w]].sz;
				ans ^= 1 << j;
				p = seg[p].s[1 ^ w];
			}
			assert(p != 0);
		}
		printf("%d\n" ,ans);
	}
}