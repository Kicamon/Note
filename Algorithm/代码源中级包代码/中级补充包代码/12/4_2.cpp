#include<bits/stdc++.h>
using namespace std;
typedef double db;

double eps = 1e-9;
const int N = 101000;
int n, st[N];
db dp[N];
struct node {
	db a, b, r, k, x, y;
	int id;
}a[N], tmp[N];
 
db slope(node &a, node &b){
	if (fabs(a.x - b.x) <= eps) return 1e9;
	return (b.y - a.y) / (b.x - a.x);
}

void solve(int l, int r){
	if (l == r) {
		dp[l] = max(dp[l], dp[l - 1]);
		a[l].y = dp[l] / (a[l].a * a[l].r + a[l].b);
		a[l].x = a[l].y * a[l].r;
		return;
	}
	int mid = (l + r) >> 1;
	solve(l, mid);
	for (int i = l; i <= r; i++) tmp[i] = a[i];
	sort(tmp + l, tmp + mid + 1, [&](node &a, node &b) {
		if (fabs(a.x - b.x) <= eps) return a.y < b.y;
		else return a.x < b.x;
	});
	sort(tmp + mid + 1, tmp + r + 1, [&](node &a, node &b) {
		return a.k < b.k;
	});
	int top = 0;
	for (int i = l; i <= mid; i++){
		while (top >= 2 && slope(tmp[st[top]], tmp[i]) >= 
			slope(tmp[st[top - 1]], tmp[st[top]])) --top;
		st[++top] = i;
	}
	for (int i = mid + 1; i <= r; i++) {
		while (top >= 2 && slope(tmp[st[top - 1]] , tmp[st[top]]) <= tmp[i].k) --top;
		int j = st[top];
		dp[tmp[i].id] = max(dp[tmp[i].id], tmp[j].x * tmp[i].a + tmp[j].y * tmp[i].b);
	}
	solve(mid + 1, r);
}

int main(){
	scanf("%d%lf", &n, &dp[0]);
	for (int i = 1; i <= n; i++){
		scanf("%lf%lf%lf", &a[i].a, &a[i].b, &a[i].r);
		a[i].k = - a[i].a / a[i].b;
		a[i].id = i;
	}
	solve(1, n);
	printf("%.3f\n", dp[n]);
}