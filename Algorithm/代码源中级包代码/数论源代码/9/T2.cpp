#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1010000;

int p[N], pr[N / 5], n, tot;
unsigned int A, B, C, mu[N], f[N], g[N];

inline unsigned int rng61() {
    A ^= A << 16;
    A ^= A >> 5;
    A ^= A << 1;
    unsigned int t = A;
    A = B;
    B = C;
    C ^= t ^ A;
    return C;
}

int main() {
    scanf("%d%u%u%u", &n, &A, &B, &C);
    for (int i = 1; i <= n; i++)
        f[i] = rng61();

    p[1] = 1; mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!p[i]) p[i] = i, mu[i] = (uint)-1, pr[++tot] = i;
        for (int j = 1; j <= tot && pr[j] * i <= n; j++) {
            p[i * pr[j]] = pr[j];
            if (p[i] == pr[j]) {
                mu[i * pr[j]] = 0;
                break;
            } else {
                mu[i * pr[j]] = (uint)-mu[i];
            }
        }
    }
    for (int d1 = 1; d1 <= n; d1++)
        for (int d2 = 1; d1 * d2 <= n; d2++)
            g[d1 * d2] += f[d1] * mu[d2];
    uint ans = 0;
    for (int i = 1; i <= n; i++) ans ^= g[i];
    printf("%u\n", ans);
}