#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1000000007;

const int N=3010;

int n, dp[N][N], mn[N][N], ans, h[N], s[N];

int main() {
    scanf("%d",&n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &h[i]);
    dp[0][1] = 1;
    for (int i = 1; i <= n; i++) {
        mn[i][i] = h[i];
        for (int j = i + 1; j <= n; j++) mn[i][j] = mn[j][i] = min(mn[i][j - 1], h[j]);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) s[j] = (s[j - 1] + dp[i - 1][j]) % mod;
        for (int j = 1; j <= n; j++) {
            if (mn[i][j] >= h[j]) dp[i][j] = s[j];
        }
    }
    int ans = 0;
    for (int j = 1; j <= n; j++)
        ans = (ans + dp[n][j]) % mod;
    printf("%d\n", ans);
}