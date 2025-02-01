#include<bits/stdc++.h>
using namespace std;
typedef double db;

double eps=1e-9;
const int N = 101000;
int n, st[N];
db dp[N];
struct node {
	db a, b, k, r, x, y;
	int id;
}a[N], tmp[N];
 
db slope(node &a, node &b){
	if (fabs(a.x - b.x) <= eps) return 1e9;
	return (b.y - a.y) / (b.x - a.x);
}

void solve(int l, int r){
	if (l==r) {
		dp[l] = max(dp[l], dp[l - 1]);
		a[l].y = dp[l] / (a[l].a * a[l].r + a[l].b);
		a[l].x = a[l].y * a[l].r;
		return;
	}
	int mid= (l + r) >> 1;
	int ql = l, qr = mid + 1;
	for (int i = l; i <= r; i++) {
		if (a[i].id <= mid) tmp[ql++] = a[i];
		else tmp[qr++] = a[i];
	}
	for (int i = l; i <= r; i++) a[i] = tmp[i];
	solve(l, mid);
	int top = 0;
	for (int i = l; i <= mid; i++){
		while (top >= 2 && slope(a[st[top]], a[i]) 
			>= slope(a[st[top - 1]], a[st[top]])) --top;
		st[++top] = i;
	}
	for (int i = mid + 1; i <= r; i++) {
		while (top >= 2 && slope(a[st[top - 1]] , a[st[top]]) <= a[i].k) --top;
		int j = st[top];
		dp[a[i].id] = max(dp[a[i].id], a[j].x * a[i].a + a[j].y * a[i].b);
	}
	solve(mid + 1, r);
	ql = l, qr = mid + 1;
	for(int i = l; i <= r; i++){
		if (ql <= mid && (qr > r || a[ql].x <= a[qr].x)) tmp[i] = a[ql++];
		else tmp[i] = a[qr++];
		// 注意：这边要写成 (x, y) 双关键字
	}
	for (int i = l; i <= r; i++) a[i] = tmp[i];
}

int main(){
	scanf("%d%lf", &n, &dp[0]);
	for (int i = 1; i <= n; i++){
		scanf("%lf%lf%lf", &a[i].a, &a[i].b, &a[i].r);
		a[i].k = - a[i].a / a[i].b;
		a[i].id = i;
	}
	sort(a + 1, a + n + 1, [&](node &a, node &b) {
		return a.k < b.k;
	});
	solve(1, n);
	printf("%.3f\n", dp[n]);
}