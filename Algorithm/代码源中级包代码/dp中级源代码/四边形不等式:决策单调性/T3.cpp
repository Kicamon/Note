#include <bits/stdc++.h>
using namespace std;
const int N = 4010;
int n, k, u[N][N], w[N][N];
int f[N], g[N];

void solve(int l, int r, int optl, int optr) {
    int m = (l + r) / 2, optm = optl;
    f[m] = g[m];
    for (int i = optl; i <= min(optr, m - 1); i++)
        if (g[i] + w[i + 1][m] < f[m]) {
            optm = i;
            f[m] = g[i] + w[i + 1][m];
        }
    if (l < m) solve(l, m - 1, optl, optm);
    if (m < r) solve(m + 1, r, optm, optr);
}

int main(){
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            while (u[i][j] > '9' || u[i][j] < '0') u[i][j]=getchar();
            u[i][j] += -u[i - 1][j - 1] + u[i][j - 1] + u[i - 1][j] - '0';
        }
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++) {
            w[i][j] = (u[j][j] - u[i - 1][j] - u[j][i - 1] + u[i - 1][i - 1]) / 2;
        }

    for (int i = 1; i <= n; i++) g[i] = (int)1e9;
    for (int i = 1; i <= k; i++){
        solve(0, n, 0, n);
        for (int i = 0; i <= n; i++) g[i] = f[i];
    }
    printf("%lld\n", f[n]);
}