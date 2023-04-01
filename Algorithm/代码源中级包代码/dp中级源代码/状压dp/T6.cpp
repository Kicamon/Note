#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define bit(x) (1 << (x))

const int N = 40;
const int M = (1 << 18) + 10;
int n, m2;
int c[N], cnt[N], id[N], w[N], ans[N], ww[N];
int dp[N][M];
vector<int> e[N];

int main() {
    scanf("%d%d",&n, &m2);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &c[i]);
        cnt[c[i]]++;
    }
    for (int i = 1; i <= n; i++)
        scanf("%d", &ww[i]);
    for (int i = 1; i <= n; i++)
        w[i] = ww[c[i]];
    int m = 0;
    for (int i = 1; i <= n; i++) {
        if (cnt[i] >= 2) id[i] = m++;
        else id[i] = -1;
    }
    // >=2, 0 ... m - 1, =1 -1
    for (int i = 1; i <= n; i++)
        c[i] = id[c[i]];
    for (int i = 0; i < m2; i++) {
        int u, v;
        scanf("%d%d",&u, &v);
        e[u].push_back(v);
    }
    memset(dp, -1, sizeof(dp));
    dp[1][0] = 0;
    for (int i = 1; i <= n; i++) {
        ans[i] = -1;
        for (int S = 0; S < bit(m); S++) if (dp[i][S] != -1) {
            // 是否要被选
            if (c[i] == -1) dp[i][S] += w[i];
            else {
                if ((S & bit(c[i])) == 0) {
                    dp[i][S | bit(c[i])] = max(dp[i][S | bit(c[i])], dp[i][S] + w[i]);
                }
            }
            ans[i] = max(ans[i], dp[i][S]);
            for (auto v : e[i]) dp[v][S] = max(dp[v][S], dp[i][S]);
        }
    }
    for (int i = 1; i <= n; i++)
        printf("%d\n",ans[i]);
}