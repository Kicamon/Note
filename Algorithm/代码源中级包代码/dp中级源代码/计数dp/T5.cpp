#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1000000007;
const int N = 201000;
int a[N], p[N], cnt[N], dp[N][2];
int n, m, k;

ll powmod(ll a, ll b) {
    ll res = 1;
    for ( ; b; b >>= 1) {
        if (b & 1) res = res * a % mod;
        a =a * a % mod;
    }
    return res;
}

ll counteq(int x, int y) { // x max = y
    if (p[x] > y || y <= 0) return 0;
    if (p[x] == y) return powmod(y, cnt[x]);
    return (powmod(y, cnt[x]) - powmod(y - 1, cnt[x]) + mod) % mod;
}

ll countleq(int x, int y) { // x max <= y
    if (p[x] > y || y <= 0) return 0;
    return powmod(y, cnt[x]);
}

void add(int &a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}

void solve() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < n + m; i++) scanf("%d" ,&a[i]);
    for (int i = 0; i < n + m - 1; i++) {
        p[i] = 0;
        cnt[i] = min({n, m, i + 1, n + m - i - 1});
    }
    for (int i = 0; i < k; i++) {
        int x, y, h;
        scanf("%d%d%d", &x, &y, &h);
        --x; --y;
        cnt[x + y]--;
        p[x + y] = max(p[x + y], h);
    }
    for (int i = 0; i <= n + m; i++) 
        dp[i][0] = dp[i][1] = 0;
    if (a[0] > a[1]) {
        puts("0");
        return;
    }
    dp[0][(a[0] == a[1])] = counteq(0, a[0]);;
    for (int i = 0; i < n + m - 2; i++) {
        // dp[i][0]      f[i] < a[i+1]    f[i+1] == a[i+1]
        if (a[i + 1] <= a[i + 2]) {
            ll p1 = counteq(i + 1, a[i + 1]) * dp[i][0] % mod;
            add(dp[i + 1][(a[i + 1] == a[i + 2])], p1);
        }
        // dp[i][1]      f[i] = a[i+1]   f[i+1] <= a[i+1]
        // f[i+1] == a[i+2]
        if (a[i + 2] <= a[i + 1]) {
            ll p2 = counteq(i + 1, a[i + 2]) * dp[i][1] % mod;
            add(dp[i + 1][1], p2);
        }
        // f[i+1] <= min(a[i+2]-1,a[i+1])
        ll p3 = countleq(i + 1, min(a[i + 2] - 1, a[i + 1])) * dp[i][1] % mod;
        add(dp[i + 1][0], p3);
    }
    printf("%d\n", dp[n + m - 2][1]);
}

int main() {
    int tc;
    scanf("%d", &tc);
    for (int i = 1; i <= tc; i++) {
        printf("Case #%d: ", i);
        solve();
    }
}