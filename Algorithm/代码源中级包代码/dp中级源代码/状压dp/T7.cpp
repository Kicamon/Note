#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define bit(x) (1 << (x))

const int N = 22;
const int M = (1 << 20) + 10;
const int mod = 998244353;

int n, a[N][N];
vector<int> e[N];
ll inv[2010];
int dp[N][M], ans[N][N];

void add(int &a, int b) {
    a += b;
    if (a >= mod) a-=mod;
}

int main() {
    scanf("%d", &n);
    inv[1] = 1;
    for (int i = 2; i <= 2000; i++)
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) 
            scanf("%d", &a[i][j]);
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) 
        for (int S = 0; S < bit(n); S++) if (dp[i][S]) {
            int s = 0;
            for (int j = 0; j < n; j++) if ((S & bit(j)) == 0)
                s += a[i][j];
            // dp[i][S] * a[i][j] / s -> dp[i+1][S | (1<<j)]
            // -> ans[i][j]
            ll tmp = (ll)dp[i][S] * inv[s] % mod;
            for (int j = 0; j < n; j++) if ((S & bit(j)) == 0) {
                ll prob = tmp * a[i][j] % mod;
                add(dp[i + 1][S | (1 << j)], prob);
                add(ans[i][j], prob);
            }
        }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            printf("%d%c", ans[i][j], " \n"[j == n - 1]);
        }
}