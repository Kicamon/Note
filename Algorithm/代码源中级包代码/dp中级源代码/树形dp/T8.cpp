#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=2010;
const ll inf = 1ll<<60;

vector<int> son[N];

int n, hp[N], sz[N];

ll dp[N][N][2]; // 0 不使用magic，1 使用magic

void dfs(int u) {
	sz[u] = 1;
	dp[u][0][0] = hp[u];
	dp[u][1][0] = inf;
	dp[u][0][1] = inf;
	dp[u][1][1] = 0;
	static ll tmp[N][2];
	for (auto v:son[u]) {
		dfs(v);
		for (int i = 0; i <= sz[u] + sz[v]; i++) {
			tmp[i][0] = tmp[i][1] = inf;
		}
		for (int i = 0; i <= sz[u]; i++) {
			for (int j = 0; j <= sz[v]; j++) {
				tmp[i + j][0] = min(tmp[i + j][0], dp[u][i][0] + dp[v][j][0] + hp[v]);
				tmp[i + j][0] = min(tmp[i + j][0], dp[u][i][0] + dp[v][j][1]);
				tmp[i + j][1] = min(tmp[i + j][1], dp[u][i][1] + min(dp[v][j][0], dp[v][j][1]));
			}
		}
		for (int i = 0; i <= sz[u] + sz[v]; i++)
			dp[u][i][0] = tmp[i][0], dp[u][i][1] = tmp[i][1];
		sz[u] += sz[v];
	}
}

void solve() {
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) {
		son[i].clear();
	}
	for (int i = 2; i <= n; i++) {
		int f;
		scanf("%d", &f);
		son[f].push_back(i);
	}
	for (int i = 1; i <= n; i++)
		scanf("%d", &hp[i]);
	dfs(1);
	for (int i = 0; i <= n; i++) {
		printf("%lld", min(dp[1][i][0], dp[1][i][1]));
		//if (i == n) printf("\n"); else printf(" ");
		printf("%c"," \n"[i == n]);
	}
}

int main() {
	int tc;
	for (scanf("%d",&tc); tc; tc--) {
		solve();
	}

}