#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5;
int n, m, k, P;
int f[N][51], dis[N];
bool v[N], pd[N][51];
vector<pair<int,int>> e[N], erev[N];

// 从n到1求最短路，从1到n去搜索

void dij() {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    memset(dis, 0x3f, sizeof(dis));
    memset(v, 0, sizeof(v));
    dis[n] = 0;
    q.push({0, n});
    while (!q.empty()) {
        int x = q.top().second;
        q.pop();
        if (v[x]) continue;
        v[x] = 1;
        for (auto p : erev[x]) {
            int y = p.first;
            if (dis[y] > dis[x] + p.second) {
                dis[y] = dis[x] + p.second;
                q.push({dis[y], y});
            }
        }
    }
}
int dp(int u, int s) {
    if(s < 0 || s > k) return 0;
    if (pd[u][s]) throw 0;
    int &ans = f[u][s];
    if (ans) return ans;
    if (u == n) ++ans;
    pd[u][s] = 1;
    for (auto p : e[u]) {
        int v = p.first;
        ans = (ans + dp(v, s - (dis[v] + p.second - dis[u]))) % P;
    }
    pd[u][s] = 0;
    return ans;
}
int main(){
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d%d", &n, &m, &k, &P);
        memset(f, 0, sizeof(f));
        memset(pd, 0, sizeof(pd));
        for (int i = 1; i <= n; i++) {
            e[i].clear();
            erev[i].clear();
        }
        for (int i = 0; i < m; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            e[u].push_back({v, w});
            erev[v].push_back({u, w});
        }
        dij();
        try {
            printf("%d\n", dp(1, k));
        } catch(int e) {
            puts("-1");
        }
    }
    return 0;
}