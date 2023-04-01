#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1001000;

int a[N], l[N], r[N], ans[N];
int n, tot;

void dfs(int u) {
	ans[u] = ++tot;
	if (l[u]) dfs(l[u]);
	if (r[u]) dfs(r[u]);
}

void build() {
	stack<int> st;
	int root = 0;
	for (int i = 1; i <= n; i++) {
		int last = 0;
		while (!st.empty() && a[st.top()] > a[i]) {
			last = st.top();
			st.pop();
		}
		if (!st.empty()) r[st.top()] = i;
		else root = i;
		l[i] = last;
		st.push(i);
	}
	dfs(root);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	build();
	for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
	puts("");
}