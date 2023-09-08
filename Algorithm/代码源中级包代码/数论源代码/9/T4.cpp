#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 10100000, M = 10000000;
int p[N], pr[N / 5], n, tot;
int phi[N];
ll sphi[N];

int main() {
    p[1] = 1; phi[1] = 1;
    for (int i = 2; i <= M; i++) {
        if (!p[i]) p[i] = i, phi[i] = i - 1, pr[++tot] = i;
        for (int j = 1; j <= tot && pr[j] * i <= M; j++) {
            p[i * pr[j]] = pr[j];
            if (p[i] == pr[j]) {
                phi[i * pr[j]] = phi[i] * pr[j];
                break;
            } else {
                phi[i * pr[j]] = phi[i] * (pr[j] - 1);
            }
        }
    }
    for (int i = 1; i <= M; i++)
        sphi[i] = sphi[i - 1] + phi[i];
    int T;
    scanf("%d", &T);
    for (int tc = 0; tc < T; tc++) {
        int n, m;
        scanf("%d%d", &n, &m);
        if (n > m) swap(n, m);
        ll ans = 0;
        for (int l = 1; l <= n; l++) {
            int r = min(n / (n / l), m / (m / l));
            // l ... r
            ans += (sphi[r] - sphi[l - 1]) * (n / l) * (m / l);
            l = r;
        }
        printf("%lld\n", ans);
    }
}