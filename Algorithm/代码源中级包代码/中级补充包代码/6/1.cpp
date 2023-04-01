#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int M = 26, N = 1010000;
struct node {
	node *son[M], *go[M], *fail;
	int cnt;
}pool[N], *cur = pool, *d[210], *q[N], *root;

node *newnode() {
	return cur++;
}
int t, n;
char tt[N];
string s;

void build() {
	t = 0;
	q[t++] = root;
	for (int i = 0; i < t; i++) {
		node *u = q[i];
		for (int j = 0; j < M; j++) {
			if (u->son[j]) {
				u->go[j] = u->son[j];
				if (u != root) u->go[j]->fail = u->fail->go[j];
				else u->go[j]->fail = root;
				q[t++] = u->son[j];
			}
			else {
				if (u != root) u->go[j] = u->fail->go[j];
				else u->go[j] = root;
			}
		}
	}	
}

int main() {
	scanf("%d", &n);
	root = newnode();
	for (int i = 0; i < n; i++) {
		scanf("%s", tt);
		int m = strlen(tt);
		node *p = root;
		for (int j = 0; j < m; j++) {
			int w = tt[j] - 'a';
			if (!p->son[w]) p->son[w] = newnode();
			p = p->son[w];
			s.push_back(tt[j]);
		}
		d[i] = p;
		s.push_back(0);
	}
	build();
	node *p = root;
	for (auto ch : s) {
		if (ch == 0) p = root;
		else p = p->go[ch - 'a'];
		p->cnt++;
	}
	for (int i = t - 1; i; i--) {
		q[i]->fail->cnt += q[i]->cnt;
	}
	for (int i = 0; i < n; i++) {
		printf("%d\n", d[i]->cnt);
	}
}