#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000;
int f[N];
ll w[N];
int n, q;

int find(int x) {
	if (f[x] == x) return x;
	int p = f[x];
	f[x] = find(p); 
	/*
	// q
	w[x] : a[x] - a[p]   
	f[p] = q   w[p] : a[p] - a[q]
	f[x] = q   w[x] : a[x] - a[q]
	// a[x] - a[p]   +  a[p] - a[q] = a[x] - a[q]*/
	w[x] = w[x] + w[p];
	return f[x];
}

int main() {
	scanf("%d%d",&n, &q);
	for (int i = 1; i <= n; i++) {
		f[i] = i;
		w[i] = 0;
	}
	ll t = 0;
	for (int i = 0; i < q; i++) {
		int ty, l, r;
		scanf("%d%d%d", &ty, &l, &r);
		l = (l + t) % n + 1;
		r = (r + t) % n + 1;
		if (ty == 2) {
			if (find(l) != find(r)) continue;
			printf("%lld\n", w[l] - w[r]);
			t = abs(w[l] - w[r]);
		} else if (ty == 1) {
			int x;
			scanf("%d" ,&x);
			if (find(l) == find(r)) continue;
			w[f[l]] = x - w[l] + w[r];
			f[f[l]] = f[r];
			// w[f[l]] = a[f[l]] - a[f[r]]
			// a[l] - a[r] = x
			//a[l] - w[l] - (a[r] - w[r])
			//a[f[l]] - a[f[r]]
		}
	}
}