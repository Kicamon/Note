#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1000000007;

const int N = 10100000, M = 10000000;
int p[N], pr[N / 5], n, tot;
int mu[N], smu[N], pw[N];

int main() {
    p[1] = 1; mu[1] = 1;
    for (int i = 2; i <= M; i++) {
        if (!p[i]) p[i] = i, mu[i] = -1, pr[++tot] = i;
        for (int j = 1; j <= tot && pr[j] * i <= M; j++) {
            p[i * pr[j]] = pr[j];
            if (p[i] == pr[j]) {
                mu[i * pr[j]] = 0;
                break;
            } else {
                mu[i * pr[j]] = -mu[i];
            }
        }
    }
    for (int i = 1; i <= M; i++)
        smu[i] = smu[i - 1] + mu[i];
    pw[0] = 1;
    for (int i = 1; i <= M; i++) {
        pw[i] = pw[i - 1] * 2 % mod;
    }
    int T;
    scanf("%d", &T);
    for (int tc = 0; tc < T; tc++) {
        int n;
        scanf("%d", &n);
        ll ans = 0;
        for (int l = 1; l <= n; l++) {
            int d = n / l, r = n / d;
            ans = (ans + 1ll * (smu[r] - smu[l - 1]) * (pw[d] - 1)) % mod;
            l = r;
        }
        if (ans < 0) ans += mod;
        printf("%lld\n", ans);
    }
}