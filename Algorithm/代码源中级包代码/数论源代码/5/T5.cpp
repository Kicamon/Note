#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 10000000;
int pr[N / 5], p[N + 100], tot;
bool vis[N + 100];
uint ans = 0, a, b;
ll l, r;

int main() {
    scanf("%lld%lld%u%u",&l, &r, &a, &b);
    p[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (!p[i]) p[i] = i, pr[++tot] = i;
        for (int j = 1; j <= tot && pr[j] * i <= N; j++) {
            p[i * pr[j]] = pr[j];
            if (p[i] == pr[j]) break;
        }
    }

    for (int j = 1; j <= tot; j++) {
        int p = pr[j];
        for (ll x = r / p * p; x >= l && x > p; x -= p)
            vis[x - l] = 1;
    }
    for (ll i = max(2ll, l); i <= r; i++) if (!vis[i - l]) {
        ans = ans ^ (a * (uint) i + b);
    }
    printf("%u\n", ans);
}