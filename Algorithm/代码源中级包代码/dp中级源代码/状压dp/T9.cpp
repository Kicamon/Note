#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define bit(x) (1 << (x))
const int mod = 1000000007;
const int N = 1030;

int n, k, mark[N][N];
int dp[N], dp2[N];

void add(int &a, int b) {
    a += b;
    if (a >= mod) a-=mod;
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < k; i++) {
        int c, r;
        scanf("%d%d",&c, &r);
        mark[c + r][c - r] = 1;
    }
    // dp[i][S] 0...9 x-1, x-2, ... x-10
    dp[0] = 1;
    for (int i = 0; i <= n; i++) {
        for (int j = i - 2; j >= 0 && j >= i - 10; j -= 2) {
            // 滚动
            for (int S = 0; S < bit(10); S++) dp2[S] = dp[S], dp[S] = 0;
            // 不连
            if (!mark[i][j]) {
                for (int S = 0; S < bit(10); S++) dp[S] = dp2[S];
            }
            // 连边
            for (int S = 0; S < bit(10); S++) if (S & bit(i - j - 1)) {
                int newS = S & (bit(10) - bit(i - j - 1));
                add(dp[newS], dp2[S]);
            }
        }
        // i -> i + 1
        for (int S = 0; S < bit(10); S++) dp2[S] = dp[S], dp[S] = 0;
        for (int S = 0; S < bit(10); S++) {
            int newS = ((S << 1) | 1) & (bit(10) - 1);
            add(dp[newS], dp2[S]);
        }
    }
    int ans = 0;
    for (int S = 0; S < bit(10); S++) add(ans, dp[S]);
    printf("%d\n", ans);
}