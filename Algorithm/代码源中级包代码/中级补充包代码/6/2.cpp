#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int M = 26, N = 6100;
struct node {
	node *son[M], *go[M], *fail;
	int mark;
}pool[N], *cur = pool, *q[N], *root;

node *newnode() {
	return cur++;
}
int t, n, m;
char tt[N];
int dp[110][N][2];
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

void upd(int &a, int b) {
	a += b;
	if (a >= 10007) a -= 10007;
}

int main() {
	scanf("%d%d", &n, &m);
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
	dp[0][0][0] = 1;
	int sz = cur - pool;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < sz; j++) {
			for (int k = 0; k <= 1; k++) if (dp[i][j][k]) {
				node *u = pool + j;
				for (int l = 0; l < M; l++) {
					upd(dp[i + 1][u->go[l] - pool][k | u->go[l]->mark],
						dp[i][j][k]);
				}
			}
		}
	}
	int ans = 0;
	for (int j = 0; j < sz; j++) upd(ans, dp[m][j][1]);
	printf("%d\n", ans);
}