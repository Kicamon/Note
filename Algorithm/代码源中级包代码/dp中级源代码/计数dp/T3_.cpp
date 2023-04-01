#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1000000007;

const int N=1010000;

int n, dp[N];

void add(int &a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}

int main() {
    scanf("%d",&n);
    if (n == 1) {
        puts("1");
        return 0;
    }
    dp[1] = 1;

    for (int j = 1; j <= n - 1; j++) {
        if (j <= 3) {
            for (int i = j + 1; i <= n; i++) add(dp[i], dp[j]);
        } else {
            for (int k = -1; k <= 1; k++) {
                for (int i = j + k; i < n; i += j) if (i > j)
                    add(dp[i], dp[j]);
            }
        }
    }

    int ans = 0;
    for (int i = 1; i < n; i++) add(ans, dp[i]);
    printf("%lld\n", 1ll * ans * n % mod);
}