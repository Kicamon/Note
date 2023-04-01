#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define bit(x) (1 << (x))

const int N = 101000;
const int M = (1 << 18) + 10;

int n, m, k, d[22][22], a[22], p[22];

typedef pair<int,int> PII;
const int inf = 1 << 30;
vector<PII> e[N];
int vis[N], dis[N];
priority_queue<PII, vector<PII>, greater<PII>> hs;

void dijkstra(int S,int n) {
    for (int i = 1; i <= n; i++) {
        dis[i] = inf;
        vis[i] = 0;
    }
    dis[S] = 0;
    hs.push({dis[S], S});
    while (!hs.empty()) {
        int u=hs.top().second;
        hs.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto p : e[u]) {
            int v = p.first;
            if (dis[v]>dis[u] + p.second) {
                dis[v]=dis[u] + p.second;
                hs.push({dis[v], v});
            }
        }
    }
}

int v1, v2;
double dp[M][20];
int main() {
    scanf("%d%d", &v1, &v2);
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        e[u].push_back({v, w});
        e[v].push_back({u, w});
    }
    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
        scanf("%d%d", &a[i], &p[i]);
    }
    a[k] = 1;
    a[k + 1] = n;
    for (int i = 0; i <= k + 1; i++) {
        dijkstra(a[i], n);
        for (int j = 0; j <= k + 1; j++) {
            d[i][j] = dis[a[j]];
        }
    }
    if (d[k][k + 1] == inf) {
        puts("-1");
        return 0;
    }
    // dp[S][i]
    for (int S = bit(k) - 1; S >= 0; S--)
        for (int i = 0; i < k; i++) if (S & bit(i)) {
            double pBad = 0.01 * p[i];
            // 有车
            double tGood = 1. * d[i][k + 1] / v2;
            // 无车
            double tBad = 1. * d[i][k + 1] / v1;
            for (int j = 0; j < k; j++) if ((S & bit(j)) == 0) {
                tBad = min(tBad, 1. * d[i][j] / v1 + dp[S | bit(j)][j]);
            }
            dp[S][i] = pBad * tBad + (1 - pBad) * tGood;
        }
    double ans = 1. * d[k][k + 1] / v1;
    for (int j = 0; j < k; j++)
        ans = min(ans, 1. * d[k][j] / v1 + dp[bit(j)][j]);
    printf("%.10f\n", ans);
}