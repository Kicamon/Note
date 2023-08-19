#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 20010000;
int p[N], pr[N / 5], n, pe[N], tot;
uint f[N], a, b, ans;

void compute(int n, function<void(int)> calcpe) {
    ans = 0;
    f[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (i == pe[i])
            calcpe(i);
        else
            f[i] = f[pe[i]] * f[i / pe[i]];
    }
    for (uint i = 1; i <= n; i++) {
        ans ^= (a * i * f[i] + b);
    }
    printf("%u\n", ans);
}

int main() {
    scanf("%d%u%u", &n, &a, &b);
    p[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!p[i])
            p[i] = i, pe[i] = i, pr[++tot] = i;
        for (int j = 1; j <= tot && pr[j] * i <= n; j++) {
            p[i * pr[j]] = pr[j];
            if (p[i] == pr[j]) {
                pe[i * pr[j]] = pe[i] * pr[j];
                break;
            } else {
                pe[i * pr[j]] = pr[j];
            }
        }
    }

    compute(n, [&](int x) { f[x] = f[x / p[x]] + 1; });

    compute(n, [&](int x) { f[x] = f[x / p[x]] + x; });

    compute(n, [&](int x) { f[x] = x / p[x] * (p[x] - 1); });

    compute(n, [&](int x) { f[x] = x == p[x] ? -1 : 0; });
}
