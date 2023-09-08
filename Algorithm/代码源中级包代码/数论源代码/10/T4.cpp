#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;

const int N = 10010000, M = 10000000;
int p[N], pr[N / 5], n, pe[N], tot;
u64 h[N];
int main() {
    p[1] = 1;
    for (int i = 2; i <= M; i++) {
        if (!p[i]) p[i] = i, pe[i] = i, pr[++tot] = i;
        for (int j = 1; j <= tot && pr[j] * i <= M; j++) {
            p[i * pr[j]] = pr[j];
            if (p[i] == pr[j]) {
                pe[i * pr[j]] = pe[i] * pr[j];
                break;
            } else {
                pe[i * pr[j]] = pr[j];
            }
        }
    }
    h[1] = 1;
    for (int i = 2; i <= M; i++) {
        if (i == pe[i]) h[i] = h[i / p[i]] + (u64)i * (i - i / p[i]);
        else h[i] = h[pe[i]] * h[i / pe[i]];
    }
    int T;
    scanf("%d", &T);
    for (int tc = 0; tc < T; tc++) {
        int n;
        scanf("%d", &n);
        u64 ans = n * (1 + h[n]) / 2;
        printf("%llu\n", ans % (1ull << 60));
    }
}