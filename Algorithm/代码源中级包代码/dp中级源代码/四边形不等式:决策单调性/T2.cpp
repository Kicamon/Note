#include <bits/stdc++.h>
using namespace std;
#define ll long long
 
const int N=5010;
int n, k, opt[N][N];
ll a[N], w[N][N], dp[N][N];
 
int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &a[i]);
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            w[i][j] = w[i][j - 1] + a[j] - a[(i + j) / 2];
        }
    }
    memset(dp , 0x3f , sizeof(dp));
    for (int i = 1; i <= n; ++i) {
        dp[1][i] = w[1][i];
        opt[1][i] = 0;
    }
    for (int i = 2; i <= k; ++i) {
        opt[i][n + 1] = n;
        for(int j = n; j >= i; j--) {
            for (int k = opt[i - 1][j]; k <= opt[i][j + 1]; k++) {
                if (dp[i][j] > dp[i - 1][k] + w[k + 1][j]) {
                    dp[i][j] = dp[i - 1][k] + w[k + 1][j];
                    opt[i][j] = k;
                }
            }
        }
    }
    printf("%lld\n",dp[k][n]);
}