#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 998244353; // 1000000007

const int N = 101000;
ll ans = 1;
int sz[N], n;
vector<int> e[N];

void dfs(int u,int f) {
    sz[u] = 1;
    int cnt = 0;
    for (auto v : e[u]) if (v != f) {
        dfs(v, u);
        sz[u] += sz[v];
        if (sz[v] % 2 == 1) cnt += 1;
    }
    if (cnt % 2 == 1) cnt += 1;
    for (int i = cnt - 1; i >= 1; i -= 2)
        ans = ans * i % mod;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1, 0);
    printf("%lld\n", ans);
}