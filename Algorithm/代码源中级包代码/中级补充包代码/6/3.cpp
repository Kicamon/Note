#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int M = 2, N = 30100;
struct node {
	node *son[M], *go[M], *fail;
	int mark, ins, vis;
}pool[N], *cur = pool, *q[N], *root;

node *newnode() {
	return cur++;
}
int t, n;
char tt[N];

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

bool dfs(node *u) {
	u->vis = 1;
	u->ins = 1;
	for (int j =0; j < M; j++) {
		if (u->go[j]->mark) continue;
		if (!u->go[j]->vis) {
			if (dfs(u->go[j])) return true;
		} else {
			if (u->go[j]->ins) return true;
		}
	}
	u->ins = 0;
	return false;
}

int main() {
	scanf("%d", &n);
	root = newnode();
	for (int i = 0; i < n; i++) {
		scanf("%s", tt);
		int m = strlen(tt);
		node *p = root;
		for (int j = 0; j < m; j++) {
			int w = tt[j] - '0';
			if (!p->son[w]) p->son[w] = newnode();
			p = p->son[w];
		}
		p->mark = 1;
	}
	build();
	for (int i = 1; i < t; i++) {
		q[i]->mark |= q[i]->fail->mark;
	}
	puts(dfs(root)?"TAK":"NIE");
}